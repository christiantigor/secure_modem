import transmit
import sys

def main():
    fileSrcMod = 'test_transmit_encrypt_fec.bit' #same file with test_fec_encrypt_fec.bit
    fileMod = 'test_transmit_mod.raw'
    fileDemod = 'test_transmit_demod.bit'

    #modulate
    transmit.modulate(fileSrcMod,fileMod)

    #demodulate
    transmit.demodulate(fileMod,fileDemod)

if __name__ == '__main__':
    try:
        main()
    except:
        print '!!! test_transmit error !!!'
        sys.exit(1)
