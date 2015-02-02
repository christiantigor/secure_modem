#software to open ref_codec_dec.pcm
#to be used for comparison with hdk sniffing

#open decoded file (.pcm)
f = open('ref_codec_dec.pcm','rb')
decodedFile = f.read()
#print decodedFile
#print len(decodedFile)
h = decodedFile.encode('hex')
print h
print len(h)
#print type(decodedFile)
