import sys
import time

i = 0
while True:
    data = 'qwerty' + str(i) + '\n'
    sys.stdout.write(data)
    time.sleep(0.5)
    print 'loop'
    i += 1

