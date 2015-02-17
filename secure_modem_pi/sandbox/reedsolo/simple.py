import reedsolo

rs = reedsolo.RSCodec(10) #nsym = 10, can correct up to nsym/2 symbol
rs1 = reedsolo.RSCodec(12) #nsym = 12, nsym is number of ECC (error correction code)

msg = 'hello world'
fec = rs.encode(msg)
fec1 = rs1.encode(msg)
print fec
print type(fec)
print len(msg)
print len(fec)
print len(fec1)

unfec = rs.decode(fec)
print unfec
print type(unfec)

msgErr = 'qwer  world'
msgErr = msgErr.encode('hex')
ecc = 'ed2554c4fdfd89f3a8aa'
msgErr = msgErr + ecc
msgErr = msgErr.decode('hex')
msgErr = bytearray(msgErr)
print type(msgErr)
print msgErr
unfec = rs.decode(msgErr)
print unfec
