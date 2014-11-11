from Crypto.Cipher import AES
import subprocess
import time

#open encoded file (.bit)
f = open('hts1a_c2.bit','r')
encodedFile = f.read()
h = encodedFile.encode('hex')
#print h
#print type(encodedFile)
l = len(encodedFile)
mod = l%16
if mod == 0:
    pass
else:
    encodedFile = encodedFile[:-mod]

#encrypt file
key = 'mysecretpassword'
encryptor = AES.new(key, AES.MODE_ECB)
encryptedVoice = encryptor.encrypt(encodedFile)
encVoHex = encryptedVoice.encode('hex')
print encVoHex

#print encryptedVoice

#write encryptedVoice to file
fi = open('hts1a_c2_enc.bit','w')
fi.write(encryptedVoice)
fi.close()

time.sleep(5)

#modulate with FDMDV
try:
    fdmdvMod = subprocess.Popen(
        ['./fdmdv_mod hts1a_c2_enc.bit hts1a_c2_enc_mod.raw'],
        stdout = subprocess.PIPE,
        stderr = subprocess.PIPE,
        shell = True
    )
    out, error = fdmdvMod.communicate()
    #print out
except subprocess.CalledProcessError:
    print '!!! modulate with FDMDV error !!!'
