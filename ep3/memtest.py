#!/usr/local/bin/python3
import sys
import subprocess

alg = sys.argv[1]

log = open ('memo'+alg+'.log', 'w')

for i in range(30):
    process = subprocess.Popen(['./roda.sh', '4', alg, '1', '9999999'], stdout=subprocess.PIPE)
    out, err = process.communicate()
    time = out.splitlines()[-3].split()[-1].decode('utf-8')
    log.write(time[0:-1] + '\n')

log.close()

