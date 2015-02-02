#software to open ref_codec_enc.bit
#to be used for comparison with hdk sniffing

#open encoded file (.bit)
f = open('ref_codec_enc.bit','rb')
encodedFile = f.read()
h = encodedFile.encode('hex')
print h
print len(h)
