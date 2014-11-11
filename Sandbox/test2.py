import subprocess
import binascii
import re

#open original data
data = '123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz'

f = open('biner.bit','w')
f.write(data)
f.close()

h = data.encode('hex')

#print ' '.join(hex(ord(i)) for i in binascii.unhexlify(h))
print len(h)
print '\n'

#modulate with FDMDV
try:
    fdmdvMod = subprocess.Popen(
        ['./fdmdv_mod biner.bit biner_mod.raw'],
        stdout = subprocess.PIPE,
        stderr = subprocess.PIPE,
        shell = True
    )
    out, error = fdmdvMod.communicate()
    #print out
except subprocess.CalledProcessError:
    print '!!! modulate with FDMDV error !!!'

#demodulate with FDMDV
try:
    fdmdvDemod = subprocess.Popen(
        ['./fdmdv_demod biner_mod.raw biner_demod.bit'],
        stdout = subprocess.PIPE,
        stderr = subprocess.PIPE,
        shell = True
    )
    out, error = fdmdvDemod.communicate()
    #print out
except subprocess.CalledProcessError:
    print '!!! demodulate with FDMDV error !!!'

#open demodulated data
f = open('biner_demod.bit','r')
r = f.read()

dh = r.encode('hex')

#print ' '.join(hex(ord(i)) for i in binascii.unhexlify(dh))
print len(dh)
print 'len difference: %d' %(len(dh)-len(h))

#regex
temp = 'startlemsanegwinend'
tempHex = temp.encode('hex')
pattern = r'start([A-za-z0-9_]*)end'
patternHex = r'7374617274([A-za-z0-9_]*)656e64'
text = re.findall(pattern, temp)
textHex = re.findall(patternHex,tempHex)
txt =textHex[0]
print txt.decode('hex')
