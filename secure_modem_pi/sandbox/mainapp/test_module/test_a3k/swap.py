#software for byte swapping
import struct
import sys

def byteswap(original,swapped):
    try:
        #open original file
        f = open(original,'rb')
        fOri = f.read()
        f.close()

        #open swapped file
        fSwap = open(swapped,'wb')

        #encode original file to hex
        h = fOri.encode('hex')
        
        #split original file to chunk
        whole = len(h)
        chunkSize = 4
        for i in range(0,whole,chunkSize):
            chunk = h[i:i+chunkSize]
            #swap byte
            chunk = chunk.decode('hex')
            a,b = struct.unpack('bb',chunk)
            chunk = struct.pack('bb',b,a)
            fSwap.write(chunk)
        fSwap.close()
    except:
        print '!!! byte swap error  !!!'
        sys.exit(1)
