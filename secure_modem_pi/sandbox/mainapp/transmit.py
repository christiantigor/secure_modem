#software for modulation (demodulation will be done on the fly)
import re
import reedsolo
import subprocess
import sys

def modulate(fileSrcMod,fileMod):
    try:
        print '[DBG]start fdmdv modulation'

        #create modulated file
        cmdCrMod = './fdmdv_mod ' + fileSrcMod + ' ' + fileMod
        procCrMod = subprocess.Popen(
            cmdCrMod,
            stdout = subprocess.PIPE,
            stderr = subprocess.PIPE,
            shell = True
        )
        procCrMod.communicate()

        #modulate file
        cmdMod = 'aplay -D plughw:RADIO -f S16_LE ' + fileMod
        procCmdMod = subprocess.Popen(
            cmdMod,
            stdout = subprocess.PIPE,
            stderr = subprocess.PIPE,
            shell = True
        )
        procCmdMod.communicate()
       
        print '[DBG]finish fdmdv modulation'
    except:
        print '!!! fdmdv modulate error !!!'
        sys.exit(1)

def demodulate(fileSrcDemod,fileDemod): #for testing only
    try:
        print '[DBG]start fdmdv demodulation'
        cmdCrDemod = './fdmdv_demod ' + fileSrcDemod + ' ' + fileDemod
        procCrDemod = subprocess.Popen(
            cmdCrDemod,
            stdout = subprocess.PIPE,
            stderr = subprocess.PIPE,
            shell = True
        )
        procCrDemod.communicate()
 
        print '[DBG]finish fdmdv demodulation'
    except:
        print '!!! fdmdv demodulate error !!!'
        sys.exit(1)
