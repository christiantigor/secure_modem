#software to record encoded file by AMBE3000 (input to usb)
#set hdkboard to idle mode
import re
import serial
import time

#configure serial
ser = serial.Serial(
    port = 'COM14',
    baudrate = 460800,
    timeout = 0.02, #period of incoming data is 20ms
    rtscts = 0,
    xonxoff = 0
)

#send opening packet
pckOp1 = '6100040400022F2D'
pckOp2 = '6100110010003200400B0709270518401500012F37'
pckOp3 = '61000A0044038002A049000A2F03'
pckOp4 = '610004002A002F01'

ser.write(pckOp1.decode('hex'))
time.sleep(0.02)
ser.write(pckOp2.decode('hex'))
time.sleep(0.02)
ser.write(pckOp3.decode('hex'))
time.sleep(0.02)
ser.write(pckOp4.decode('hex'))
time.sleep(0.02)

#read serial then save to file
f = open('rec_manual_raw.bit','wb+')
for _ in range(100):
    s = ser.read(25)
    hexa = s.encode('hex')
    #print s
    #print hexa
    #print '\n'
    f.write(hexa)
f.close()

#process raw file to generate audio file
#fRaw = open('rec_manual_ref.bit','rb') #use reference file
fRaw = open('rec_manual_raw.bit','rb') #use recorded file
raw = fRaw.read()
fRaw.close()
#print raw

#remove response of opening packet
pckOpRspn1 = '6100010401'
pckOpRspn2 = '610010001000320040000b000900050015002f4f'
pckOpRspn3 = '61000600440049002f24'
pckOpRspn4 = '610004002a002f01'

raw = re.sub(pckOpRspn1,'',raw,count=1)
raw = re.sub(pckOpRspn2,'',raw,count=1)
raw = re.sub(pckOpRspn3,'',raw,count=1)
raw = re.sub(pckOpRspn4,'',raw,count=1)
#print raw

#open audio file
fAudio = open('rec_manual_audio.bit','wb')

#split raw file to chunk
whole = len(raw)
chunkSize = 40
for i in range(0,whole,chunkSize):
    chunk = raw[i:i+chunkSize]
    if len(chunk) == 40:
        chunk = chunk[12:] #remove pckHeader
        chunk = chunk[:-10] #remove pckSmplsCmodPrtyId
        chunk = chunk.decode('hex') #convert to ascii
        fAudio.write(chunk)
fAudio.close()

#send closing packet
pckCl1 = '610003002B2F07'
pckCl2 = '6100040400002F2F'
ser.write(pckCl1.decode('hex'))
time.sleep(0.02)
ser.write(pckCl2.decode('hex'))
time.sleep(0.02)
