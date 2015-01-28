#software to play encoded file by AMBE3000 (input to p1)
#set hdkboard to a3kdirect mode
import re
import serial
import time

#configure serial
ser = serial.Serial(
    port = 'COM4',
    baudrate = 460800,
    timeout = 1,
    rtscts = 0,
    xonxoff = 0
)

#send opening packet
pckOp1 = '61002C0038004749000A44038002A044038001414403800483440380053E44038005BB440380060448008049000A2F56'
pckOp2 = '6100110010003200400B0709270518401500012F37'
pckOp3 = '61000A0044038002A049000A2F03'
pckOp4 = '610004002A002F01' #codec start

ser.write(pckOp1.decode('hex'))
time.sleep(0.02)
ser.write(pckOp2.decode('hex'))
time.sleep(0.02)
ser.write(pckOp3.decode('hex'))
time.sleep(0.02)
ser.write(pckOp4.decode('hex'))
time.sleep(0.02)

#open encoded file
#f = open('rec_ref_play_a.bit','rb') #open recorded file using hdkcom
f = open('rec_manual_audio.bit','rb') #open recorded file using python
encodedFile = f.read()
h = encodedFile.encode('hex')

#split encoded file to chunk
whole = len(h)
chunkSize = 18
chunks = []
pckHeader = '0012010148'
pckSmplsCmodPrtyId = '03A00210402F'
for i in range(0,whole,chunkSize):
    chunk = h[i:i+chunkSize]
    chunk = pckHeader + chunk + pckSmplsCmodPrtyId
    #print chunk
    chunks.append(chunk)
#print chunks

#calculate parity of each chunk
byteSize = 2
pckStart = '61'
for i in range(len(chunks)):
    xorRslt = 0
    #xor each byte in chunk
    for j in range(0, len(chunks[i]), byteSize):
        byte = chunks[i][j:j+2]
        num = int(byte,16)
        xorRslt = xorRslt ^ num
    if xorRslt < 16:
        pckPrty = str(format(xorRslt, 'x'))
        pckPrty = '0' + pckPrty
    else:
        pckPrty = str(format(xorRslt, 'x'))
    chunks[i] = pckStart + chunks[i] + pckPrty
    #print chunks[i]
#print chunks[0]

#send chunk per 20ms
#print len(chunks)
for i in range(len(chunks)-1):
    asciiChunk = chunks[i].decode('hex')
    ser.write(asciiChunk)
    time.sleep(0.02)
    
#send closing packet
pckCl1 = '610003002B2F07' #codec stop
#pckCl2 = '6100040400002F2F' #packet type 0x04 is for hdk
#pckCl3 = '61000900342600000700002F33' #reset ambe to use ppt iface without codec
ser.write(pckCl1.decode('hex'))
time.sleep(0.02)
#ser.write(pckCl2.decode('hex'))
#time.sleep(0.02)
#ser.write(pckCl3.decode('hex'))
#time.sleep(0.02)

