import RPi.GPIO as GPIO
import time
import subprocess

GPIO.setmode(GPIO.BCM)
OFF_BUTTON = 23
LED = 18
GPIO.setup(OFF_BUTTON, GPIO.IN)
GPIO.setup(LED, GPIO.OUT)

prevOffInput = None

if __name__ == '__main__':
    try:
         while True:
             offInput = GPIO.input(OFF_BUTTON)
             if((not offInput) and prevOffInput): #active low
                 print 'OFF_BUTTON is pressed'
                 prevOffInput = False
                 offProcess = subprocess.Popen(
                     ['sudo shutdown -h now'],
                     stdout = subprocess.PIPE,
                     stderr = subprocess.PIPE,
                     shell = True
                 )
                 offOut, offError = offProcess.communicate()
                 print offOut
             elif(offInput and (not prevOffInput)):
                 print 'OFF_BUTTON is released'
                 prevOffInput = True
             else:
                 pass
             time.sleep(0.1)
    except:
         print '!!! buttonoff error !!!'
