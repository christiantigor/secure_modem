import kripto
import sys

def main():

    fileEncod = 'test_kripto_encod.bit' #same file with test_a3k_encod.bit
    fileEncrypt = 'test_kripto_encrypt.bit'
    fileDecrypt = 'test_kripto_decrypt.bit'
    fileNoEncrypt = 'test_kripto_no_encrypt.bit'
    fileNoDecrypt = 'test_kripto_no_decrypt.bit'
    key = 'mysecretpassword'

    kripto.aesEncrypt(fileEncod,fileEncrypt,key)
    kripto.aesDecrypt(fileEncrypt,fileDecrypt,key)

    kripto.noEncrypt(fileEncod,fileNoEncrypt)
    kripto.noDecrypt(fileNoEncrypt,fileNoDecrypt)

if __name__ == '__main__':
    try:
        main()
    except:
        print '!!! test_kripto error !!!'
        sys.exit(1)
