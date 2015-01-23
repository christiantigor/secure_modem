#sending ascii to hdk board and show it response in hex
import serial
import time

#configure serial
ser = serial.Serial(
    port = 'COM14',
    baudrate = 460800,
    timeout = 1
)
ser.close()
ser.open()

enHdkMode = '6100040400092F26'
quHdkMode = '6100040400002F2F'
asciiEn = enHdkMode.decode('hex')
asciiQu = quHdkMode.decode('hex')
#print asciiEn
#print asciiQu
ser.write(asciiEn)
rspn = ser.read(1024)
print 'enter hdk mode'
print rspn.encode('hex')
time.sleep(5)
ser.write(asciiQu)
rspn = ser.read(1024)
print 'quit hdk mode'
print rspn.encode('hex')
