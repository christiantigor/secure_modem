#software for encrypt, and modulate the encoded (c2) audio wave

from Crypto.Cipher import AES
import subprocess
import time

#open encoded file (.bit)
f = open('hts1a_c2.bit','r')
encodedFile = f.read()
#h = encodedFile.encode('hex')
#print h
#print type(encodedFile)

#check len of encoded file
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
#print encryptedVoice

#add start and end indicator to encryptedVoice
start = 'securemodemstart'
end = 'securemodemend'
start = start.encode('hex')
end = end.encode('hex')
encVoHex = start + encVoHex + end

#multiply encVoHex
encVoHex = encVoHex + encVoHex + encVoHex
print encVoHex

#decode back encVoHex
encVo = encVoHex.decode('hex')

#write encVoHex to file
fi = open('hts1a_c2_enc.bit','w')
fi.write(encVo)
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
    print "!!! hts1a_c2_enc_mod.raw created !!!"
    #print out
except subprocess.CalledProcessError:
    print '!!! modulate with FDMDV error !!!'

#transmit via analog radio
#play -r 8000 -s -2 hts1a_c2_enc_mod.raw #not tested yet on real transmission
