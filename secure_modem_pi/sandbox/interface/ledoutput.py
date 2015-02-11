import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
LED = 18
GPIO.setup(LED, GPIO.OUT)

if __name__ == '__main__':
    try:
        GPIO.output(LED, True)
        time.sleep(5)
        GPIO.output(LED, False)
    except:
        print '!!! ledoutput error  !!!'
