import os
import RPi.GPIO as GPIO
import signal
import subprocess
import time

GPIO.setmode(GPIO.BCM)
PTT_BUTTON = 23
LED = 18
GPIO.setup(PTT_BUTTON, GPIO.IN)
GPIO.setup(LED, GPIO.OUT)

prevPttInput = None

if __name__ == '__main__':
    try:
         while True:
             pttInput = GPIO.input(PTT_BUTTON)
             if((not pttInput) and prevPttInput): #active low
                 print 'PTT_BUTTON is pressed'
                 prevPttInput = False
                 cmd = 'arecord -D plughw:1,0 -t raw test.raw'
                 pttProcess = subprocess.Popen(
                     cmd,
                     stdout = subprocess.PIPE,
                     shell = True,
                     preexec_fn = os.setsid
                 )
                 time.sleep(5)
                 os.killpg(pttProcess.pid, signal.SIGTERM)
             elif(pttInput and (not prevPttInput)):
                 print 'PTT_BUTTON is released'
                 prevPttInput = True
             else:
                 pass
             time.sleep(0.1)
    except:
         print '!!! buttonptt error !!!'
