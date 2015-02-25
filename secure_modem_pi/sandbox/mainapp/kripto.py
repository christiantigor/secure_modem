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

        #check length of file (multiple of 16)
        size = 16
        mod = len(fEncod)%size
        fEncod = fEncod + ((size - mod) * '0')

        #encrypt file
        encryptor = AES.new(key, AES.MODE_ECB)
        encrypted = encryptor.encrypt(fEncod)

        #print '[DBG]encrypt file'

        #write to file
        fEncrypt = open(fileEncrypt,'wb')
        fEncrypt.write(encrypted)
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

        #check lenght of file (multiple of 16) ???

        #decrypt file
        decryptor = AES.new(key, AES.MODE_ECB)
        decrypted = decryptor.decrypt(fDemod)

        #srite to file
        fDecrypt = open(fileDecrypt,'wb')
        fDecrypt.write(decrypted)
        fDecrypt.close()

        print '[DBG]finish aes decryption'
    except:
        print 'aes decrypt error'
        sys.exit(1)
