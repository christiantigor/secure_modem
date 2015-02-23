#software for encoding and decoding by a3k
import re
import serial
import sys
import swap
import time

def encode(fileRaw,fileEncod):
    try:
        print '[DBG]start a3k encode'        

        #swap byte
        idx = fileRaw.find('.raw')
        fileRawSwap = fileRaw[:idx] + '_swap' + fileRaw[idx:]
        swap.byteswap(fileRaw, fileRawSwap)

        #open file
        f = open(fileRawSwap,'rb')
        fRaw = f.read()
        f.close()

        #encode file to hex
        h = fRaw.encode('hex')        

        #split file to chunk
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
            chunks.append(chunk)
        
        #calculate parity of each chunk
        byteSize = 2
        pckStart = '61'
        for i in range(len(chunks)):
            xorRslt = 0
            #xor each byte in chunk
            for j in range(0,len(chunks[i]),byteSize):
                byte = chunks[i][j:j+byteSize]
                num = int(byte,16)
                xorRslt = xorRslt ^ num
                pckPrty = str(format(xorRslt,'x'))
            if xorRslt < 16:
                pckPrty = '0' + pckPrty
            else:
                pass
            chunks[i] = pckStart + chunks[i] + pckPrty

        #init serial
        ser = serial.Serial(
            port = '/dev/ttyUSB0',
            baudrate = 115200,
            timeout = 0.1,
            rtscts = 0,
            xonxoff = 0
        )

        #print '[DBG]init serial'

        #send opening packet
        pckOp1 = '6100110010003200400B0709270518401500012F37'
        ser.write(pckOp1.decode('hex'))
        time.sleep(0.02)

        #print '[DBG]send opening packet'

        #send speech packet
        s = ''
        for chunk in chunks:
            ser.write(chunk.decode('hex'))
            rspn = ser.read(25)
            s += rspn.encode('hex')

        #print '[DBG]send speech packet'

        #remove response of opening packet
        pckOpRspn1 = '6100010401'
        pckOpRspn2 = '610010001000320040000b000900050015002f4f'
        s = re.sub(pckOpRspn1,'',s,count=1)
        s = re.sub(pckOpRspn2,'',s,count=1)

        #print '[DBG]rmv rspns of opening packet'

        #open encoded file
        fEncod = open(fileEncod,'wb')

        #split response of speech packet to chunk
        whole = len(s)
        chunkSize = 40
        for i in range(0,whole,chunkSize):
            chunk = s[i:i+chunkSize]
            if len(chunk) == 40:
                chunk = chunk[12:] #remove pckStart and pckHeader
                chunk = chunk[:-10] #remove pckCmode and pckPrty
                chunk = chunk.decode('hex')
                fEncod.write(chunk)
        fEncod.close()

        print '[DBG]finish a3k encode'
    except:
        print 'a3k encode error'
        sys.exit(1)
