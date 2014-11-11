from Crypto.Cipher import AES
import subprocess

#demodulate with FDMDV
try:
    fdmdvDemod = subprocess.Popen(
        ['./fdmdv_demod hts1a_c2_enc_mod.raw hts1a_c2_enc_demod.bit'],
        stdout = subprocess.PIPE,
        stderr = subprocess.PIPE,
        shell = True
    )
    out, error = fdmdvDemod.communicate()
    #print out
except subprocess.CalledProcessError:
    print '!!! modulate with FDMDV error !!!'

#open demodulated file (.bit)
f = open('hts1a_c2_enc_demod.bit','r')
demodulatedFile = f.read()
h = demodulatedFile.encode('hex')
print h
l = len(demodulatedFile)
mod = l%16
if mod == 0:
    pass
else:
    demodulatedFile = demodulatedFile[:-mod]


#decrypt file
key = 'mysecretpassword'
decryptor = AES.new(key, AES.MODE_ECB)
decryptedVoice = decryptor.decrypt(str(demodulatedFile))

#write decryptedVoice to file
fi = open('hts1a_c2_dec.bit','w')
fi.write(decryptedVoice)
fi.close()

#decoding with codec2
