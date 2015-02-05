#software to swap byte of audio .pcm or .bit file
import struct
import sys

def swap(fName,svAsName):
    try:
        #open audio file
        f = open(fName,'rb')
        oriAudio = f.read()
        f.close()

        #open swapped audio file
        fSwap = open(svAsName,'wb')
        
        h = oriAudio.encode('hex')

        #split audio file to chunk
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
        print "!!! byte swap error !!!"
        sys.exit(1)
