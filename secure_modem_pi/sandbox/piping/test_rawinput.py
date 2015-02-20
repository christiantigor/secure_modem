try:
    while True:
        s = raw_input('input: \n')
        print len(s)
        s += '\n'
        print len(s)
except:
    print '!!! rawinput error  !!!'
