import re
import reedsolo

try:
    padSize = 5
    padSt = padSize * 'a' #start of whole data
    padEn = padSize * 'z' #end of whole data
    isData = None
    data = ''
    isNewData = None
    while True:
        s = raw_input()
        #append new line char
        s += '\n'
        #check if data
        if re.search(padSt,s):
            isData = True
        elif re.search(padEn,s):
            data += s
            isData = False
            isNewData = True
            #print data
        else:
            pass
        #get data between start and end
        if isData:
            data += s
        else:
            pass

        #process new data
        try:
            if isNewData:
                #save new data
                f = open('rec_modulation_demod.bit','wb')
                f.write(data)
                f.close()

                h = data.encode('hex')
                pattern = re.compile(r'(?<=5354)(\S*?)(?=454e)') #ST=5354 and EN=454e
                chunks = re.findall(pattern,h)
                #print chunks
                print len(chunks)

                #unfec reedsolo
                nsym = 100 #can correct up to nsym/2 error
                rs = reedsolo.RSCodec(nsym)
                unfecs = []
                for chunk in chunks:
                    c = bytearray(chunk.decode('hex'))
                    #print len(c)
                    unfec = rs.decode(c) #still no handling when it's error
                    unfecs.append(unfec)

                #write unfec file
                fUnfec = open('rec_manual_unfec.bit','wb')
                for unfec in unfecs:
                    fUnfec.write(unfec)
                fUnfec.close()

                print 'new data'
                isNewData = False
                data = ''
            else:
                pass
        except:
            print '!!! process new data error  !!!'
        
except:
    print '!!! read raw data error  !!!'
