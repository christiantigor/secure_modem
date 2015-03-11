#arecord -D plughw:RADIO -f S16_LE -t raw | python test_pipe.py

import serial
import struct
import subprocess
import sys
import time

def byteSwap(data): #data in hex
    whole = len(data)
    chunkSize = 4
    byteSwapped = ''
    for i in range(0,whole,chunkSize):
        chunk = data[i:i+chunkSize]
        #swap byte
        chunk = chunk.decode('hex')
        a,b = struct.unpack('bb',chunk)
        chunk = struct.pack('bb',b,a)
        byteSwapped += chunk.encode('hex')
    return byteSwapped

def calcParity(data): #data in hex
    byteSize = 2
    xorRslt = 0
    #xor each byte in data
    for j in range(0,len(data),byteSize):
        byte = data[j:j+byteSize]
        num = int(byte,16)
        xorRslt = xorRslt ^ num
        pckPrty = str(format(xorRslt,'x'))
    if xorRslt < 16:
        pckPrty = '0' + pckPrty
    else:
        pass
    return pckPrty

def main():
    encodeSize = 640
    isNewData = None
    buff = ''
    data = ''

    #start a3k variable
    pckStart = '61'
    pckHeader = '01470200A0'
    pckCmode = '0210402F'
    #end a3k variable

    #init serial
    ser = serial.Serial(
        port = '/dev/ttyUSB0',
        baudrate = 115200,
        timeout = 0.5,
        rtscts = 0,
        xonxoff = 0
    )
   
    #init a3k
    #pckOp1 = '6100110010003200400B0709270518401500012F37'
    #ser.write(pckOp1.decode('hex'))

    #init subprocess
    cmdPlay = 'aplay -D plughw:USER -f S16_LE'
    p = subprocess.Popen(
        cmdPlay,
        stdout = subprocess.PIPE,
        stdin = subprocess.PIPE,
        stderr = subprocess.PIPE,
        shell = True        
    )

    while True:
        #get data stream
        s = raw_input()
        s = s.encode('hex')
        s += '0A' #append new line char

        #put stream to buffer
        buff += s

        #check if enough stream to encode
        if len(buff) > encodeSize:
            data = buff[0:encodeSize]
            buff = buff[encodeSize:] #remove encoded stream from buffer
            isNewData = True
        else:
            pass

        #process new data
        if isNewData:
            #swap byte
            data = byteSwap(data)
            
            #construct data to encode
            data = pckHeader + data + pckCmode
            pckPrty = calcParity(data)
            data = pckStart + data + pckPrty
            
            #encode data with a3k
            ser.write(data.decode('hex'))
            rspnEnc = ser.read(25)
            rspnEncHex = rspnEnc.encode('hex')
            #print rspnEncHex
            
            #decode data with a3k
            ser.write(rspnEncHex.decode('hex'))
            rspnDec = ser.read(640)
            rspnDecHex = rspnDec.encode('hex')
            dataRecv = rspnDecHex
            #print rspnDecHex

            #deconstruct data from decode
            dataRecv = dataRecv[12:]
            dataRecv = dataRecv[:-4]
            dataRecv = byteSwap(dataRecv)
            print len(dataRecv)

            #play decoded data
            #comm = p.communicate(input=dataRecv.decode('hex'))
            #print comm
            p.stdin.write(dataRecv.decode('hex'))

            #reset new data variable
            isNewData = False
            data = ''
        else:
            pass

if __name__ == '__main__':
    try:
        main()
    except:
        print '!!! test_pipe error !!!'
        sys.exit(1)
