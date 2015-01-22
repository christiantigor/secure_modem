#software for open rec_reference.bit
#to be used for comparison with hdk sniffing

#open encoded file (.bit)
f = open('rec_ref_play.bit','r')
encodedFile = f.read()
h = encodedFile.encode('hex')
print h
#print type(encodedFile)
