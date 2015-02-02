#software to open ref_codec_dec_byte_swap.pcm

#open decoded file (.pcm)
f = open('ref_codec_dec_byte_swap.pcm','rb')
decodedFile = f.read()
#print decodedFile
#print len(decodedFile)
h = decodedFile.encode('hex')
print h
print len(h)
#print type(decodedFile)
