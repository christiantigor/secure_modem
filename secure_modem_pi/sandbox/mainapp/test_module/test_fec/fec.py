#software for fec and unfec
import re
import reedsolo
import sys

def fec(fileSrcFec):
    try:
        #open file
        f = open(fileSrcFec,'rb')
        fSrcFec = f.read()
        f.close()

        #encode file to hex
        h = fSrcFec.encode('hex')

        #split file to chunk
        whole = len(h)
        chunkSize = 2*16 #a3k encoding size (9 byte) in 16 byte chunk
        chunks = []
        for i in range(0,whole,chunkSize):
            chunk = h[i:i+chunkSize]
            if len(chunk) < chunkSize:
                #print 'should never happen in encryption mode'
                chunk = chunk.ljust(chunkSize,'0')
            chunks.append(chunk)

        #fec reedsolo and add ST and EN flags
        nsym = 16 #can correct up to nsym/2 error
        rs = reedsolo.RSCodec(nsym)
        flagSt = 'ST'
        flagEn = 'EN'
        fecs = []
        for chunk in chunks:
            #fec reedsolo
            c = bytearray(chunk.decode('hex'))
            fec = rs.encode(c)

            #add flags
            fec = flagSt + fec + flagEn
            fecs.append(fec)

        #open fec file
        idx = fileSrcFec.find('.bit')
        fileFec = fileSrcFec[:idx] + '_fec' + fileSrcFec[idx:]
        fFec = open(fileFec,'wb')

        #add padding at front
        padSize = 128
        padSt = padSize * 'a'
        padEn = padSize * 'z'
        fFec.write(padSt)

        #write data to fec file
        for fec in fecs:
            fFec.write(fec)

        #add padding at back
        fFec.write(padEn)
        fFec.close()

    except:
        print '!!! fec error !!!'
        sys.exit(1)

def unfec(fileSrcUnfec):
    try:
        #open file
        f = open(fileSrcUnfec,'rb')
        fSrcUnfec = f.read()
        f.close()

        #encode file to hex
        h = fSrcUnfec.encode('hex')

        #find chunk
        pattern = re.compile(r'(?<=5354)(\S*?)(?=454e)') #ST=5354 and EN=454e
        chunks = re.findall(pattern,h)
        print len(chunks)

        #unfec reedsolo
        chunkSize = 2*16
        nsym = 16 #can correct up to nsym/2 error
        rs = reedsolo.RSCodec(nsym)
        unfecs = []
        for chunk in chunks:
            c = bytearray(chunk.decode('hex'))
            if len(c) == chunkSize:
                sys.stdout.write('.')
                unfec = rs.decode(c) #handle error when len != chunkSize
                unfecs.append(unfec)
            else:
                pass

        #open unfec file
        idx = fileSrcUnfec.find('.bit')
        fileUnfec = fileSrcUnfec[:idx] + '_unfec' + fileSrcUnfec[idx:]
        fUnfec = open(fileUnfec,'wb')

        #write unfec file
        for unfec in unfecs:
            fUnfec.write(unfec)
        fUnfec.close()

        print ''

    except:
        print '!!! unfec error !!!'
        sys.exit(1)
