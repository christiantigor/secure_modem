#open file
f = open('test.raw','rb')
file = f.read()
h = file.encode('hex')
print h
print len(h)
