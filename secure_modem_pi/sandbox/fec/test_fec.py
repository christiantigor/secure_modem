#create reliable transmission
#add fec before modulation

import subprocess

#file name
srcFileName = 'manual_enc.bit'

#create share files
numShare = 8
fecCmd = 'zfec -p fec -m ' + str(numShare)  +' -f ' + srcFileName
#print fecCmd
fec = subprocess.Popen(
    fecCmd,
    shell = True
)

#read, add flags, and combine all share files
stFlag = 'stFEC'
enFlag = 'ENfec'
stFlag = stFlag.encode('hex')
enFlag = enFlag.encode('hex')

cmbnFileName = 'fec_combine.bit'
cmbnFile = open(cmbnFileName,'wb')
for i in range(numShare):
    #read
    shareName = 'fec.' + str(i) + '_' + str(numShare) + '.fec'
    f = open(shareName,'rb')
    share = f.read()
    share = share.encode('hex')
    f.close()
    #add flags
    share = stFlag + share + enFlag
    cmbnFile.write(share.decode('hex'))
cmbnFile.close()

#modulate
modCmd = './fdmdv_mod ' + cmbnFileName + ' modulation.raw'
fdmdvMod = subprocess.Popen(
    modCmd,
    shell = True
)

#demodulate (just for testing)
#./fdmdv_demod modulation.raw modulation_demod.bit
#./fdmdv_demod rec_modulation.raw rec_modulation_demod.bit
