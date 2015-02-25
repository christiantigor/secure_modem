import fec
import sys

def main():
    fileSrcFec = 'test_fec_encrypt.bit' #same file with test_kripto_encrypt.bit

    #fec
    fec.fec(fileSrcFec)
    
    idx = fileSrcFec.find('.bit')
    fileFec = fileSrcFec[:idx] + '_fec' + fileSrcFec[idx:]

    #unfec
    fec.unfec(fileFec)

if __name__ == '__main__':
    try:
        main()
    except:
        print '!!! test_fec error !!!'
        sys.exit(1)
