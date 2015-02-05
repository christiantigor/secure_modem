#software to open ref_codec_dec_dec.pcm
#to be used for comparison with hdk sniffing

#open decoded file (.pcm)
f = open('ref_codec_dec_dec.pcm','rb')
decodedFile = f.read()
#print decodedFile
#print len(decodedFile)
h = decodedFile.encode('hex')
print h[0:640]
print h[641:1280]
print len(h)
#print type(decodedFile)
