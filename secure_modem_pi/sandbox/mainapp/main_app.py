import os
import re
import reedsolo
import RPi.GPIO as GPIO
import signal
import subprocess
import time    

def main():
    ###init io###
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    #input
    BUTTON_OFF = 17
    BUTTON_PTT = 23
    SW_1 = 24
    SW_2 = 25
    GPIO.setup(BUTTON_OFF, GPIO.IN)
    GPIO.setup(BUTTON_PTT, GPIO.IN)
    GPIO.setup(SW_1, GPIO.IN)
    GPIO.setup(SW_2, GPIO.IN)
    #output
    LED_PTT = 18
    LED_ON_OFF = 27
    GPIO.setup(LED_PTT, GPIO.OUT)
    GPIO.setup(LED_ON_OFF, GPIO.OUT)

    ###init parameter###
    prevInOff = None
    prevInPtt = None
    prevInSw1 = None
    prevInSw2 = None

    #turn LED_ON_OFF on
    GPIO.output(LED_ON_OFF, True)

    print 'secure_modem start'
    
    while True:
        #check BUTTON_PTT
        inPtt = GPIO.input(BUTTON_PTT)
        if((not inPtt) and prevInPtt): #active low
            #print 'ptt is pressed - record voice'
            GPIO.output(LED_PTT, True)
            prevInPtt = False

            #record voice
            cmdRec = 'arecord -D plughw:USER -t raw man_rec.raw'
            procRec = subprocess.Popen(
                cmdRec,
                stdout = subprocess.PIPE,
                shell = True,
                preexec_fn = os.setsid
            )
            while(not GPIO.input(BUTTON_PTT)):
                pass
            os.killpg(procRec.pid, signal.SIGTERM)
            
        elif(inPtt and (not prevInPtt)):
            #print 'ptt is released - listen to voice'
            GPIO.output(LED_PTT, False)
            prevInPtt = True
        else:
            pass
        time.sleep(0.1)
            #record voice
                #check to use encryption
                #transmit voice
            #listen to voice
                #check if use encryption
                #play voice

        #check BUTTON_OFF
        inOff = GPIO.input(BUTTON_OFF)
        if((not inOff) and prevInOff): #active low
            #print 'turn device off'
            GPIO.output(LED_ON_OFF, False)
            prevInOff = False
            procOff = subprocess.Popen(['sudo shutdown -h now'], shell = True)
        elif(inOff and (not prevInOff)):
            #print 'keep device on'
            prevInOff = True
        else:
            pass
        time.sleep(0.1)

if __name__ == '__main__':
    main()
