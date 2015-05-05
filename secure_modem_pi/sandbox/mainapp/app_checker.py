#software for checking if app_sender.py and app_receiver.py are running

import subprocess
import sys
import re

def main():
    try:
        #sender
        sender = 'app_sender.py'
        pySender = 'python ' + sender
        cSender = 'ps -ef | grep ' + sender
        pSender = subprocess.Popen(
            cSender,
            stdout = subprocess.PIPE,
            stderr = subprocess.PIPE,
            shell = True
        )
        oSender, eSender = pSender.communicate()

        if oSender:
            if re.search(pySender, oSender):
                print 'app_sender.py is running'
                #return
            else:
                print 'app_sender.py is not running'
                print 're-run'
                subprocess.Popen(['sudo python app_sender.py'], shell = True)
        else:
            print 'oSender empty'
            #return

        #receiver
        rcvr = 'app_receiver.py'
        pyRcvr = 'python ' + rcvr
        cRcvr = 'ps -ef | grep ' + rcvr
        pRcvr = subprocess.Popen(
            cRcvr,
            stdout = subprocess.PIPE,
            stderr = subprocess.PIPE,
            shell = True
        )
        oRcvr, eRcvr = pRcvr.communicate()

        if oRcvr:
            if re.search(pyRcvr,oRcvr):
                print 'app_rcvr.py is running'
                return
            else:
                print 'app_receiver.py is not running'
                print 're-run'
                subprocess.Popen(['arecord -D plughw:RADIO -f S16_LE -t raw | ./fdmdv_demod - - | sudo python app_receiver.py'], shell = True)
        else:
            print 'oRcvr empty'
            return
    except:
        print '!!! app_checker error !!!'
        sys.exit(1)

if __name__ == '__main__':
    main()
