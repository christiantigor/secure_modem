import subprocess

try:
    cmd = 'arecord -D plughw:RADIO -f S16_LE -t raw | ./fdmdv_demod - - | python app_receiver.py &'
    subprocess.Popen([cmd], shell = True)
except:
    print '!!! start_app_receiver error !!!'
