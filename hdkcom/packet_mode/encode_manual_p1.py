#software to encode, byte swapped pcm file (input to p1)
#set hdkboard to a3kdirect mode

import re
import serial
import time
import byte_swap

#configure serial
ser = serial.Serial(
    port = 'COM4',
    baudrate = 460800,
    timeout = 0.02,
    rtscts = 0,
    xonxoff = 0
)

#send opening packet
pckOp1 = '6100110010003200400B0709270518401500012F37'

ser.write(pckOp1.decode('hex'))
time.sleep(0.02)

#swap byte of pcm file
byte_swap.swap('rec_packet_raw.pcm','rec_packet_raw_byte_swap.pcm')


#open byte swapped pcm file
f = open('rec_packet_raw_byte_swap.pcm','rb') #open manually recorded file
#f = open('ref_codec_dec_byte_swap.pcm','rb') #open recorded file by hdkcom
fPcm = f.read()
f.close()

h = fPcm.encode('hex')

#split audio file to chunk
whole = len(h)
chunkSize = 640
chunks = []
pckHeader = '01470200A0'
pckCmode = '0210402F'
for i in range(0,whole,chunkSize):
    chunk = h[i:i+chunkSize]
    if len(chunk) < chunkSize:
        chunk = chunk.ljust(chunkSize,'0')
    chunk = pckHeader + chunk + pckCmode
    #print chunk
    chunks.append(chunk)

#calculate parity of each chunk then send to vocoder
byteSize = 2
pckStart = '61'
s = ''
for i in range(len(chunks)):
    xorRslt = 0
    #xor each byte in chunk
    for j in range(0,len(chunks[i]),byteSize):
        byte = chunks[i][j:j+2]
        num = int(byte,16)
        xorRslt = xorRslt ^ num
    if xorRslt < 16:
        pckPrty = str(format(xorRslt,'x'))
        pckPrty = '0' + pckPrty
    else:
        pckPrty = str(format(xorRslt,'x'))
    chunks[i] = pckStart + chunks[i] + pckPrty
    #print chunks[i]
    #send chunk continuously
    ser.write(chunks[i].decode('hex'))
    rspn = ser.read(25)
    s += rspn.encode('hex')
    #print rspn.encode('hex')
#print s

#remove response of opening packet
pckOpRspn1 = '6100010401'
pckOpRspn2 = '610010001000320040000b000900050015002f4f'

s = re.sub(pckOpRspn1,'',s,count=1)
s = re.sub(pckOpRspn2,'',s,count=1)
#print s

#open encoded file
fEncoded = open('manual_enc.bit','wb')

#split response of speech packet to chunk
whole = len(s)
chunkSize = 40
for i in range(0,whole,chunkSize):
    chunk = s[i:i+chunkSize]
    if len(chunk) == 40:
        chunk = chunk[12:] #remove pckStart and pckHeader
        chunk = chunk[:-10] #remove pckCmode and pckPrty
        chunk = chunk.decode('hex')
        fEncoded.write(chunk)
fEncoded.close()
