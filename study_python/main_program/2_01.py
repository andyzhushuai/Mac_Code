import sys
print >> sys.stderr, 'fatal error: invalid input!'
logfile = open('/tmp/mylog.txt','a')
print >> logfile, 'fatal error: invalid input!'
logfile.close()
