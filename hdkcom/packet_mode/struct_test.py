#software to test struct in python
import struct
import array

data = 'FFFB'
ascii = data.decode('hex')
#print len(ascii)
#print struct.calcsize('>bb')
a,b = struct.unpack('bb',ascii)
#print a, b
s = struct.pack('bb',b,a)
print s.encode('hex')

s = 'a1a2a3a4a5a6a7a8'
a = array.array('h',s)
a.byteswap()
rslt = a.tostring()
print rslt
