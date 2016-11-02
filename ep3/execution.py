from memory import Memory
import utility as ut
import math

def run (trace, m_alg, p_alg, inter):
    file = open (trace, "r")
    a = list (map (int, file.readline ().split ()))
    s = a[2]
    p = a[3]
    physical = Memory (a[0], '/tmp/ep3.mem', s) 
    virtual = Memory (a[1], '/tmp/ep3.vir', s) 
    proc = ut.Process (file.readline ().split ())
    ut.running += 1
    time = proc.t0
    while True:
        while proc != None and proc.t0 == time:
            virtual.insert (proc, m_alg)
            atr = file.readline ().split ()
            if atr != []:
                proc = ut.Process (atr)
                ut.running += 1
            else:
                proc = None

        if time % inter == 0:
            virtual.show ()

        if proc == None and ut.running == 3:
            break

        time += 1
    file.close ()
