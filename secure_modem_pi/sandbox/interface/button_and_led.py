import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
BUTTON = 23
LED = 18
GPIO.setup(BUTTON, GPIO.IN)
GPIO.setup(LED, GPIO.OUT)

prevInput = None

if __name__ == '__main__':
    try:
         while True:
             input = GPIO.input(BUTTON)
             if((not input) and prevInput): #active low
                 print 'button is pressed'
                 GPIO.output(LED, True)
                 prevInput = False
             elif(input and (not prevInput)):
                 print 'button is released'
                 GPIO.output(LED, False)
                 prevInput = True
             else:
                 pass
             time.sleep(0.1)
    except:
         print '!!! buttonandled error !!!'
