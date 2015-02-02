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

#open audio file
##f = open('ref_codec_dec.pcm','rb')
##oriAudio = f.read()
##f.close()

#open byte swapped audio file
#fSwap = open('rec_packet_raw_byte_swap.pcm','wb')
##fSwap = open('ref_codec_dec_byte_swap.pcm','wb') #for development only

##h = oriAudio.encode('hex')

#split audio file to chunk
##whole = len(h)
##chunkSize = 4
##for i in range(0,whole,chunkSize):
##    chunk = h[i:i+chunkSize]
    #print chunk
    #swap byte
##    chunk = chunk.decode('hex')
##    a,b = struct.unpack('bb',chunk)
##    chunk = struct.pack('bb',b,a)
    #chunk = chunk.encode('hex')
    #print '> %s' % chunk
##    fSwap.write(chunk)
##fSwap.close()
