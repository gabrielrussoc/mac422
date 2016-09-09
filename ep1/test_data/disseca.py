import os
import sys
import glob

pessoa = sys.argv[1]

os.chdir(pessoa)
print("Entrei em " + pessoa)

for size in ['small', 'medium', 'large']:
    print("Tipo: "+ size)
    os.chdir(size)
    for sched in ['fcfs', 'srtn', 'multi']:
        print("Escalonador: "+sched)
        os.chdir(sched)
        write = open('../../../'+pessoa+'-'+size+'-'+sched+'.csv', 'w')
        write.write('deadline,context')
        for out in glob.glob("*.out"):
            print(out)
            loc = list(open(out, 'r'))
            deadline = (loc[-1].split())[0] #deadline
            context = (loc[-2].split())[0] #context
            write.write(deadline+','+context)
        write.close()
        os.chdir('..')
    os.chdir('..')

