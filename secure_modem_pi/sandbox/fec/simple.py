import zfec

print zfec.Encoder(2,3).encode(['ab','cd'])
print zfec.Decoder(2,3).decode(['ab','en',],[0,2])

#zfec manual_enc.bit #split file
#zunfec -o fec_result.bit -f manual_enc.bit.1_8.fec manual_enc.bit.5_8.fec manual_enc.bit.7_8.fec

