from memory import Memory
from pages import Pages
import utility as ut
import math

def load (trace):
    file = open (trace, "r")
    ret = []
    for line in file:
        ret.append (ut.Process (file.readline ().split ()))
    file.close ()
    return ret

def run (trace, m_alg, p_alg, inter):
    #total virtual s p
    a = list (map (int, file.readline ().split ()))
    s = int (a[2])
    p = int (a[3])
    physical = Memory (a[0], '/tmp/ep3.mem', s, p) 
    virtual = Memory (a[1], '/tmp/ep3.vir', s, p) 
    pq = ut.ProcessQueue ()
    rq = ut.RunningQueue ()
    pgt = Pages (physical, virtual, p_alg)
    time = index = 0
    timeline = load (trace)
    if p_alg == 1:
        pgt.optimal_init (timeline)
    while True:
        while index < len (timeline) and timeline[index].t0 == time:
            proc = timeline[index]
            pq.push (proc)
            rq.push (proc)
            proc.base = virtual.insert (proc, m_alg)
            index += 1

        while pq.get_size () > 0 and pq.top ().next_time () == time:
            ac_proc = pq.top ()
            pgt.access (ac_proc) 
            pq.pop ()

        while rq.get_size () > 0 and rq.top ().tf == time:
            virtual.remove (rq.top ())
            rq.pop ()
        
        if time % inter == 0:
            virtual.show ()
            physical.show ()

        if index == len (timeline) and rq.get_size () == 0:
            break

        time += 1
