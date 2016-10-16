#!/usr/bin/python3
import subprocess
import math
import re
import sys

fn = 42
fd = 1000

modo = sys.argv[1]

for i in ['small','medium','large']:
    if modo == 'n':
        f = open('test_data/fn-'+i+'.in', 'r')
        d = int(f.read())
        n = fn
        out = open('test_data/fn'+'-'+i+'.csv', 'w')
    else:
        f = open('test_data/fd-'+i+'.in', 'r')
        d = fd
        n = int(f.read())
        out = open('test_data/fd'+'-'+i+'.csv', 'w')

    #fixado-tamanho.out
    print (i)
    print (str(d) + ' ' + str(n))
    for fox in range(30):
        print ('.', end='')
        args = '/usr/bin/time -v ./ep2 '+str(d)+' '+str(n)+' u'
        popen = subprocess.Popen(args.split(), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = popen.communicate()[1].decode('ascii')
        timeRegex = re.compile('Elapsed \(wall clock\) time \(h:mm:ss or m:ss\): .*')
        memoryRegex = re.compile('Maximum resident set size \(kbytes\): [0-9]+')
        time = timeRegex.search(output).group().split()[-1]
        memory = memoryRegex.search(output).group().split()[-1]
        minute = float(time.split(':')[0])
        sec = float(time.split(':')[1])
        out.write (str(minute*60 + sec) + ';' + str(memory) + '\n')
        sys.stdout.flush()
    print()
    out.close()
    f.close()

