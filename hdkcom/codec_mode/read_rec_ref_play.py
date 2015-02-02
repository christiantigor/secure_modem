#software for open rec_ref_play.bit
#to be used for comparison with hdk sniffing

#open encoded file (.bit)
f = open('rec_ref_play.bit','rb')
encodedFile = f.read()
#print encodedFile
#print len(encodedFile)
h = encodedFile.encode('hex')
print h
print len(h)
#print type(encodedFile)
