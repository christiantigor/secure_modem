#software to open rec_ref_record.bit
#to be used for comparison with hdk sniffing

#open encoded file (.bit)
f = open('rec_ref_record.bit','rb')
encodedFile = f.read()
h = encodedFile.encode('hex')
print h
#print type(encodedFile)
