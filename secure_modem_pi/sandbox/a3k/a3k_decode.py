#software to decode bit file
#set hdkboard to a3kdirect mode

import re
import serial
import time
import byte_swap

#configure serial
ser = serial.Serial(
    port = '/dev/ttyUSB0',
    baudrate = 115200,
    timeout = 0.1,
    rtscts = 0,
    xonxoff = 0
)

#send opening packet
pckOp1 = '6100110010003200400B0709270518401500012F37'

ser.write(pckOp1.decode('hex'))
time.sleep(0.02)

#open bit file
f = open('manual_enc.bit','rb') #open manually recorded file
#f = open('ref_codec_enc.bit','rb') #open recorded file by hdkcom
fBit = f.read()
f.close()

h = fBit.encode('hex')
#print h

#split encoded file to chunk
whole = len(h)
chunkSize = 18
chunks = []
pckHeader = '0012010148'
pckCmode = '03A00200002F'
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
        byte = chunks[i][j:j+byteSize]
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
    rspn = ser.read(640)
    s += rspn.encode('hex')
    #print rspn.encode('hex')
#print s

#remove response of opening packet
pckOpRspn1 = '6100010401'
pckOpRspn2 = '610010001000320040000b000900050015002f4f'

s = re.sub(pckOpRspn1,'',s,count=1)
s = re.sub(pckOpRspn2,'',s,count=1)
print s[0:100]
print len(s)

#open decoded file
fEncoded = open('manual_dec_unswapped.pcm','wb')

#split response of speech packet to chunk
whole = len(s)
chunkSize = 656 #640 bytes of data and 16 bytes of pckStart + pckHeader + pckPrty
for i in range(0,whole,chunkSize):
    chunk = s[i:i+chunkSize]
    #print chunk
    #print '\n'
    if len(chunk) == chunkSize:
        chunk = chunk[12:] #remove pckStart and pckHeader
        chunk = chunk[:-4] #remove pckCmode and pckPrty
        chunk = chunk.decode('hex')
        fEncoded.write(chunk)
fEncoded.close()

#swap byte of pcm file
byte_swap.swap('manual_dec_unswapped.pcm','manual_dec.pcm')

#play decoded file
#aplay -D plughw:1,0 -f S16_LE -t raw manual_dec.pcm
