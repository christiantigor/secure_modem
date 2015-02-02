#software to open rec_packet_raw.pcm
#to be used for comparison with hdk sniffing

#open raw file (.pcm)
f = open('rec_packet_raw.pcm','rb')
rawFile = f.read()
#print rawFile
#print len(rawFile)
h = rawFile.encode('hex')
print h
print len(h)
#print type(rawFile)
