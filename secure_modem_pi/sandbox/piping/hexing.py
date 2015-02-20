import re

#file to open
f = open('rec_modulation_demod.bit','rb')
data = f.read()
f.close()

#encode to hex
h = data.encode('hex')

#search chunk
pattern = re.compile(r'(?<=5354)(\S*?)(?=454e)')#ST=5354 and EN=454e
chunks = re.findall(pattern,h)

#print
byteSize = 2
for chunk in chunks:
    chunkSp = ' '.join(chunk[i:i+byteSize] for i in xrange(0,len(chunk),byteSize))
    print chunkSp
    print 'Length: %d\n' % len(chunk)
    #search new line char
    for j in range(0,len(chunk),byteSize):
        if chunk[j:j+byteSize] == '0a': #new line = 0x0a
            print 'new line found'
        else:
            pass
