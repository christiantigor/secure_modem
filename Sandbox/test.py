from Crypto.Cipher import AES
import subprocess
import time

#open encoded file (.bit)
f = open('hts1a_c2.bit','r')
encodedFile = f.read()
h = encodedFile.encode('hex')

#trim encodedFile so that it will be multiple of 16 in length (trimmed .bit file can be played after decoded back)
l = len(encodedFile)
mod = l%16
if mod == 0:
    pass
else:
    encodedFile = encodedFile[:-mod]

#write edited encoded file (.bit)
#f = open('hts1a_c2_edited.bit','w')
#f.write(encodedFile)
#f.close()

#encrypt file
key = 'mysecretpassword'
encryptor = AES.new(key, AES.MODE_ECB)
encryptedVoice = encryptor.encrypt(encodedFile)

#print encryptedVoice

#write encryptedVoice to file
f = open('hts1a_c2_enc.bit','w')
f.write(encryptedVoice)
f.close()

time.sleep(5)

#open encryptedVoice
f = open('hts1a_c2_enc.bit','r')
encryptedVoiceFromFile = f.read()

#decrypt file
decryptor = AES.new(key, AES.MODE_ECB)
decryptedVoice = decryptor.decrypt(encryptedVoiceFromFile)

#write decryptedVoice to file
f = open('hts1a_c2_dec.bit','w')
f.write(decryptedVoice)
f.close()
