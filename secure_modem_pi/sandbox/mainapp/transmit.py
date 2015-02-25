#software for modulation and demodulation
import re
import reedsolo
import subprocess
import sys

def modulate(fileSrcMod,fileMod):
    try:
        print '[DBG]start fdmdv modulation'

        #open file
        f = open(fileSrcMod,'rb')
        fSrcMod = f.read()
        f.close()

        #encode file to hex
        h = fSrcMod.encode('hex')

        #split file to chunk
        whole = len(h)
        chunkSize = 300 #one sym is to bytes, we use 150 sym
        chunks = []
        for i in range(0,whole,chunkSize):
            chunk = h[i:i+chunkSize]
            if len(chunk) < chunkSize:
                chunk = chunk.ljust(chunkSize,'0')
            chunks.append(chunk)

        #fec reedsolo and add ST and EN flags
        nsym = 100 #can correct up to nsym/2 error
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
        idx = fileSrcMod.find('.bit')
        fileSrcModFec = fileSrcMod[:idx] + '_fec' + fileSrcMod[idx:]
        fFec = open(fileSrcModFec,'wb')

        #add padding at front
        padSize = 255
        padSt = padSize * 'a'
        padEn = padSize * 'z'
        fFec.write(padSt)

        #write data to fec file
        for fec in fecs:
            fFec.write(fec)

        #add padding at back
        fFec.write(padEn)
        fFec.close()

        #create modulated file
        cmdCrMod = './fdmdv_mod ' + fileSrcModFec + ' ' + fileMod
        procCrMod = subprocess.Popen(
            cmdCrMod,
            stdout = subprocess.PIPE,
            stderr = subprocess.PIPE,
            shell = True
        )
        procCrMod.communicate()

        #modulate file
        cmdMod = 'aplay -D plughw:RADIO -f S16_LE ' + fileMod
        procCmdMod = subprocess.Popen(
            cmdMod,
            stdout = subprocess.PIPE,
            stderr = subprocess.PIPE,
            shell = True
        )
        procCmdMod.communicate()
       
        print '[DBG]finish fdmdv modulation'
    except:
        print 'fdmdv modulate error'
        sys.exit(1)

def unfec(fileDemod,chunkSize):
    try:
        print '[DBG]start unfec'

        #open file
        f = open(fileDemod,'rb')
        fDemod = f.read()
        f.close()

        #encode file to hex
        h = fDemod.encode('hex')
        pattern = re.compile(r'(?<=5354)(\S*?)(?=454e)') #ST=5354 and EN=454e
        chunks = re.findall(pattern,h)
        #print chunks
        print len(chunks)

        #unfec reedsolo
        nsym = 100 #can correct ip to nsym/2 error
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

        #write unfec file
        fUnfec = open(fileDemod,'wb')
        for unfec in unfecs:
            fUnfec.write(unfec)
        fUnfec.close()

        print ''
        print '[DBG]finish unfec'
    except:
        print 'unfec error'
        sys.exit(1)
