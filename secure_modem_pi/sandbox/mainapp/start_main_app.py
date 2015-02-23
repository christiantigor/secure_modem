import subprocess

try:
    cmd = 'arecord -D plughw:RADIO -f S16_LE -t raw | ./fdmdv_demod - - | python main_app.py &'
    subprocess.Popen([cmd], shell = True)
except:
    print '!!! start_main_app error !!!'
