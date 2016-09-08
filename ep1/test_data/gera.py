import random as rnd
import sys

n = int(sys.argv[1])
k = 3
proc = 0
t0 = 0

while proc < n:
    t0 += rnd.uniform (0, 2)
    dt = rnd.uniform (0.1, 10)
    deadline = rnd.uniform (1, 3) * dt + t0
    print (str(t0) + " process" + str(proc) + " " + str(dt) + " " + str(deadline))
    proc += 1
        
