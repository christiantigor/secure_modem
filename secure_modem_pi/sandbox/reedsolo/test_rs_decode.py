#create reliable transmission
#decode fec after demodulation

import subprocess
import reedsolo
import re

#open file
#f = open('manual_fec.bit','rb') #should open file result of demodulation
#f = open('modulation_demod.bit','rb') #without transmission
f = open('rec_modulation_demod.bit','rb')
fDemod = f.read()
f.close()

h = fDemod.encode('hex')
#print h
#print len(h)

#search chunks between start and end flags
flagSt = 'ST' #5354
flagEn = 'EN' #454e
pattern = re.compile(r'(?<=5354)(\S*?)(?=454e)')
chunks = re.findall(pattern,h)
#print chunks
print len(chunks)

#unfec reedsolo
nsym = 100 #can correct up to nsym/2 error
rs = reedsolo.RSCodec(nsym)
unfecs = []
for chunk in chunks:
    c = bytearray(chunk.decode('hex'))
    print len(c)
    unfec = rs.decode(c)
    unfecs.append(unfec)

#write unfec file
#fUnfec = open('manual_unfec.bit','wb')
fUnfec = open('rec_manual_unfec.bit','wb')
for unfec in unfecs:
    fUnfec.write(unfec)
fUnfec.close()

#demodulate (just for testing)
#./fdmdv_demod modulation.raw modulation_demod.bit
#./fdmdv_demod rec_modulation.raw rec_modulation_demod.bit
