#software for demodulate, decrypt and decode the audio wave, so it can be played on receiver end

from Crypto.Cipher import AES
import subprocess
import re

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
    print '!!! demodulate with FDMDV error !!!'

#open demodulated file (.bit)
f = open('hts1a_c2_enc_demod.bit','r')
demodulatedFile = f.read()
demFilHex = demodulatedFile.encode('hex')
#print demFilHex

#regex based on start and end keyword
start = 'securemodemstart' #7365637572656d6f64656d7374617274
end = 'securemodemend' #7365637572656d6f64656d656e64
start = start.encode('hex')
end = end.encode('hex')
pattern = r'7365637572656d6f64656d7374617274([A-za-z0-9_]*)7365637572656d6f64656d656e64'
encryptedVoice = re.findall(pattern,demFilHex)
#print encryptedVoice
if len(encryptedVoice) > 0:
    encVoHex = encryptedVoice[0]
    #print encVoHex
    print '!!! stream found !!!'
else:
    print '!!! no stream found !!!'


#must not be used
#l = len(demodulatedFile)
#mod = l%16
#if mod == 0:
#    pass
#else:
#    demodulatedFile = demodulatedFile[:-mod]


#decrypt file
encVo = encVoHex.decode('hex')
key = 'mysecretpassword'
decryptor = AES.new(key, AES.MODE_ECB)
decryptedVoice = decryptor.decrypt(encVo)

#write decryptedVoice to file
fi = open('hts1a_c2_dec.bit','w')
fi.write(decryptedVoice)
fi.close()

#decoding with codec2
#./c2dec 2400 hts1a_c2_dec.bit hts1a_dec.raw
try:
    c2Dec = subprocess.Popen(
        ['./c2dec 2400 hts1a_c2_dec.bit hts1a_dec.raw'],
        stdout = subprocess.PIPE,
        stderr = subprocess.PIPE,
        shell = True
    )
    out, error = c2Dec.communicate()
    print "!!! hts1a_dec.raw created !!!"
    #print out
except:
    print "!!! decoding with c2 error !!!"

#play audio on receiver end
#play -r 8000 -s -2 hts1a_dec.raw
