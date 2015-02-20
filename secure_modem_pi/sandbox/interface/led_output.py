import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
LED_PTT = 18
LED_ON_OFF = 27
GPIO.setup(LED_PTT, GPIO.OUT)
GPIO.setup(LED_ON_OFF, GPIO.OUT)

if __name__ == '__main__':
    try:
        GPIO.output(LED_PTT, True)
        GPIO.output(LED_ON_OFF, True)
        time.sleep(5)
        GPIO.output(LED_PTT, False)
        GPIO.output(LED_ON_OFF, False)
    except:
        print '!!! ledoutput error  !!!'
