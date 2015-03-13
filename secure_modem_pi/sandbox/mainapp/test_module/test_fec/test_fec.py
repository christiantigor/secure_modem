import fec
import sys

def main():
    fileSrcFec = 'test_fec_encrypt.bit' #same file with test_kripto_encrypt.bit
    fileSrcError = 'test_fec_encrypt_fec_error.bit' #test for error occurence
                  #'test_fec_encrypt_fec.bit' is the correct file

    #fec
    fec.fec(fileSrcFec)
    
    #correct file
    idx = fileSrcFec.find('.bit')
    fileFec = fileSrcFec[:idx] + '_fec' + fileSrcFec[idx:]

    #test using ERROR file
    fileFec = fileSrcError

    #unfec
    fec.unfec(fileFec)

if __name__ == '__main__':
    try:
        main()
    except:
        print '!!! test_fec error !!!'
        sys.exit(1)
