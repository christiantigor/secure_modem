#software to open rec_packet_enc.bit
#to be used for comparison with hdk sniffing

#open encoded file (.enc)
f = open('rec_packet_enc.bit','rb')
encodedFile = f.read()
#print encodedFile
#print len(encodedFile)
h = encodedFile.encode('hex')
print h
print len(h)
#print type(encodedFile)
