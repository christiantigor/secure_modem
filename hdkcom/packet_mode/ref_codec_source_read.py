#software to open ref_codec_source.bit

#open source file (.bit)
f = open('ref_codec_source.bit','rb')
srcFile = f.read()
#print srcFile
#print len(srcFile)
h = srcFile.encode('hex')
print h
print len(h)
#print type(srcFile)
