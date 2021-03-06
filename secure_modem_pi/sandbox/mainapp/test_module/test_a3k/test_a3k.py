import a3k
import os
import RPi.GPIO as GPIO
import signal
import subprocess
import sys
import time

def main():
    #GPIO.setwarnigs(False)
    GPIO.setmode(GPIO.BCM)
    #input
    BUTTON_PTT = 23
    GPIO.setup(BUTTON_PTT, GPIO.IN)
    #output
    LED_PTT = 18
    global LED_ON_OFF
    LED_ON_OFF = 27
    GPIO.setup(LED_PTT, GPIO.OUT)
    GPIO.setup(LED_ON_OFF, GPIO.OUT)

    #init parameter
    prevInPtt = None

    fileRaw = 'test_a3k_raw.raw'
    fileEncod = 'test_a3k_encod.bit'
    fileDecod = 'test_a3k_decod.raw'

    GPIO.output(LED_ON_OFF, True)

    print 'test_a3k start'

    while True:
        #check BUTTON_PTT
        inPtt = GPIO.input(BUTTON_PTT)
        if((not inPtt) and prevInPtt): #active low
            #print 'ptt is pressed - record voice'
            GPIO.output(LED_PTT, True)
            prevInPtt = False

            #record voice
            cmdRec = 'arecord -D plughw:USER -f S16_LE -t raw ' + fileRaw
            procRec = subprocess.Popen(
                cmdRec,
                stdout = subprocess.PIPE,
                shell = True,
                preexec_fn = os.setsid
            )
            while(not GPIO.input(BUTTON_PTT)):
                pass
            os.killpg(procRec.pid, signal.SIGTERM)
            GPIO.output(LED_PTT, False)
         
            #encode voice
            a3k.encode(fileRaw,fileEncod)
        
            #decode voice
            a3k.decode(fileEncod,fileDecod)
        
            #play voice
            cmdPlay = 'aplay -D plughw:USER -f S16_LE ' + fileDecod
            procPlay = subprocess.Popen(
                cmdPlay,
                stdout = subprocess.PIPE,
                stderr = subprocess.PIPE,
                shell = True
            )
            print '[DBG]finish play voice'
        elif(inPtt and (not prevInPtt)):
            GPIO.output(LED_PTT, False)
            prevInPtt = True
        else:
            pass
        time.sleep(0.1)

if __name__ == '__main__':
    try:
        main()
    except:
        GPIO.output(LED_ON_OFF, False)
        print '!!! test_a3k error !!!'
        sys.exit(1)
