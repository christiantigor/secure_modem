#!/bin/sh
date >>/home/pi/dev/secure_modem_pi/sandbox/mainapp/crondate.txt
cd /
cd home/pi/dev/secure_modem_pi/sandbox/mainapp
python app_checker.py &
