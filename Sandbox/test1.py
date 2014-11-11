import zfec

enc = zfec.Encoder(4,10).encode(['ab','cd','ef','gh'])
print enc

dec = zfec.Decoder(4,10).decode(['\x91\x03','%s','s<','FT'],[7, 4, 5, 6])
print dec
