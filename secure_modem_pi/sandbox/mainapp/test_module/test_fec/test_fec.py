import fec
import sys

def main():
    fileSrcFec = 'test_fec_encrypt.bit' #same file with test_kripto_encrypt.bit
    fileFecError = 'test_fec_encrypt_fec_error.bit' #test for error occurence

    #fec
    fec.fec(fileSrcFec)
    
    #correct file
    idx = fileSrcFec.find('.bit')
    fileFec = fileSrcFec[:idx] + '_fec' + fileSrcFec[idx:]

    #test for error file
    fileFec = fileSrcError

    #unfec
    fec.unfec(fileFec)

if __name__ == '__main__':
    try:
        main()
    except:
        print '!!! test_fec error !!!'
        sys.exit(1)
