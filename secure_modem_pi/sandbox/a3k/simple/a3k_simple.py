#software to test if custom a3k module working properly

import serial
import time

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
rspn = ser.read(25)
print rspn.encode('hex')
