import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
SW_1 = 24
SW_2 = 25
GPIO.setup(SW_1, GPIO.IN)
GPIO.setup(SW_2, GPIO.IN)

prevInSW_1 = None
prevInSW_2 = None

if __name__ == '__main__':
    try:
        while True:
            inSW_1 = GPIO.input(SW_1)
            inSW_2 = GPIO.input(SW_2)

            if((not inSW_1) and prevInSW_1):
                print 'switch 1 is on'
                prevInSW_1 = False
            elif(inSW_1 and (not prevInSW_1)):
                print 'switch 1 is off'
                prevInSW_1 = True
            else:
                pass
            time.sleep(0.1)
    except:
        print '!!! switch_input error  !!!'
