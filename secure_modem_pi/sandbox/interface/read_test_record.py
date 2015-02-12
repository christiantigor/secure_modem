f = open('test_record.raw','rb')
file = f.read()
h = file.encode('hex')
print h
print len(h)
