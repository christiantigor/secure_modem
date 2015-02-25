#software for listening, processing, and playing voice
#how to run this file:
#arecord -D plughw:RADIO -f S16_LE -t raw | ./fdmdv_demod - - | sudo python app_receiver.py

import a3k
import fec
import kripto
import re
import RPi.GPIO as GPIO
import subprocess
import sys
import time
import transmit

def main():
    ###init io ###
    GPIO.setmode(GPIO.BCM)
    #input
    BUTTON_PTT = 23
    SW_2 = 25
    GPIO.setup(BUTTON_PTT, GPIO.IN)
    GPIO.setup(SW_2, GPIO.IN)

    ###init parameter ###
    prevInPtt = None
    prevInSw2 = None

    padSize = 5
    padSt = padSize * 'a' #start of whole data
    padEn = padSize * 'z' #end of whole data
    chunkSize = 250 #150 bytes of data and 100 bytes of fec #NOT relevant anymore
    isData = None
    data = ''
    isNewData = None

    fileDemod = 'arecv_demod.bit'
    fileDecrypt = 'arecv_decrypt.bit'
    fileDecod = 'arecv_decod.raw'

    key = 'mysecretpassword'

    print 'app_receiver start'

    while True:
        while GPIO.input(BUTTON_PTT): #ptt is released - listen to voice
            s = raw_input()
            #print s
            #append new line char
            s += '\n'
            #check if data
            if re.search(padSt,s):
                isData = True
            elif re.search(padEn,s):
                data += s
                isData = False
                isNewData = True
                #print data
            else:
                pass
            #get data between start and end
            if isData:
                data += s
            else:
                pass

            #process new data
            try:
                if isNewData:
                    #save new data
                    f = open(fileDemod,'wb')
                    f.write(data)
                    f.close()

                    #unfec voice
                    fileSrcUnfec = fileDemod
                    fec.unfec(fileSrcUnfec)

                    #unfec file name
                    idx = fileSrcUnfec.find('.bit')
                    fileUnfec = fileSrcUnfec[:idx] + '_unfec' + fileSrcUnfec[idx:]

                    #decrypt voice
                    inSw2 = GPIO.input(SW_2)
                    if(not inSw2):
                        #print 'decrypted'
                        fileDemod = fileUnfec #naming issue for ease of use
                        kripto.aesDecrypt(fileDemod,fileDecrypt,key)
                        fileSrcDecod = fileDecrypt
                    else:
                        print 'not decrypted'
                        fileSrcDecod = fileUnfec

                    #decode voice
                    print fileSrcDecod
                    a3k.decode(fileSrcDecod,fileDecod)

                    #play voice
                    cmdPlay = 'aplay -D plughw:USER -f S16_LE ' + fileDecod
                    procPlay = subprocess.Popen(
                        cmdPlay,
                        stdout = subprocess.PIPE,
                        stderr = subprocess.PIPE,
                        shell = True
                    )
                    
                    print 'new data have been processed'
                    isNewData = False
                    data = ''
                else:
                    pass
            except:
                print '!!! process new data error !!!'
                sys.exit(1)            
        #while ptt is pressed - do nothing

if __name__ == '__main__':
    try:
        main()
    except:
        print '!!! app_receiver error  !!!'
        sys.exit(1)
