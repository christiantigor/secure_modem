#software for encryption and decryption
from Crypto.Cipher import AES
import sys
import time

def aesEncrypt(fileEncod,fileEncrypt,key):
    try:
        print '[DBG]start aes encryption'

        #open file
        f = open(fileEncod,'rb')
        fEncod = f.read()
        f.close()

        #print '[DBG]open file'

        #encode file to hex
        h = fEncod.encode('hex')

        #split file to chunk
        whole = len(h)
        chunkSize = 18 #a3k encoding size (9 byte)
        chunks = []
        for i in range(0,whole,chunkSize):
            chunk = h[i:i+chunkSize]
            if len(chunk) < chunkSize:
                print 'should never happen'
                #should never happen as file must be multiply of chunkSize
            else:
                pass
            chunk = chunk.decode('hex')
            chunks.append(chunk)

        #encrypt file
        size = 16 #aes input must be multiple of 16
        encryptor = AES.new(key, AES.MODE_ECB)
        s = ''

        for chunk in chunks:
            mod = len(chunk)%size
            chunk = chunk + ((size - mod) * '0')
            encrypted = encryptor.encrypt(chunk)
            s += encrypted

        #print '[DBG]encrypt file'

        #write to file
        fEncrypt = open(fileEncrypt,'wb')
        fEncrypt.write(s)
        fEncrypt.close()

        print '[DBG]finish aes encryption'
    except:
        print 'aes encrypt error'
        sys.exit(1)

def aesDecrypt(fileDemod,fileDecrypt,key):
    try:
        print '[DBG]start aes decryption'

        #open file
        f = open(fileDemod,'rb')
        fDemod = f.read()
        f.close()

        #encode file to hex
        h = fDemod.encode('hex')

        #split file to chunk
        whole = len(h)
        chunkSize = 2*16 #a3k encoding size (9 byte) in 16 byte chunk
        encodingSize = 18 #a3k encoding size (9 byte)
        chunks = []
        for i in range(0,whole,chunkSize):
            chunk = h[i:i+chunkSize]
            if len(chunk) < chunkSize:
                print 'should never happen'
            else:
                pass
            chunk = chunk.decode('hex')
            chunks.append(chunk)

        #decrypt file
        decryptor = AES.new(key, AES.MODE_ECB)
        pad = (chunkSize-encodingSize)/2 #div 2 bcs already in ascii format
        s = ''

        for chunk in chunks:
            decrypted = decryptor.decrypt(chunk)
            decrypted = decrypted[:-pad]
            s += decrypted

        #write to file
        fDecrypt = open(fileDecrypt,'wb')
        fDecrypt.write(s)
        fDecrypt.close()

        print '[DBG]finish aes decryption'
    except:
        print 'aes decrypt error'
        sys.exit(1)
