#create reliable transmission
#add fec(reed-solomon) before modulation

import subprocess
import reedsolo

#open file
f = open('manual_enc.bit','rb')
fSrc = f.read()
f.close()

h = fSrc.encode('hex')

#split file to chunk
whole = len(h)
chunkSize = 300 #one sym is two bytes
chunks = []
for i in range(0,whole,chunkSize):
    chunk = h[i:i+chunkSize]
    if len(chunk) < chunkSize:
        chunk = chunk.ljust(chunkSize,'0')
    #print chunk
    chunks.append(chunk)

#fec reedsolo and add ST and EN flags
nsym = 100 #can correct up to nsym/2 error
rs = reedsolo.RSCodec(nsym)
flagSt = 'ST'
flagEn = 'EN'
fecs = []
for chunk in chunks:
    #reedsolo
    c = bytearray(chunk.decode('hex'))
    fec = rs.encode(c)
    #print len(fec)
    #fec = str(fec)
    #print fec.encode('hex')

    #add flags
    fec = flagSt + fec + flagEn
    fecs.append(fec)

#combine file
fFec = open('manual_fec.bit','wb')
for fec in fecs:
    fFec.write(fec)
fFec.close()

#modulate (just for testing)
#./fdmdv_mod manual_fec.bit modulation.raw
