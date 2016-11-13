from memory import Memory
import utility as ut
import math

def run (trace, m_alg, p_alg, inter):
    file = open (trace, "r")
    #total virtual s p
    a = list (map (int, file.readline ().split ()))
    s = a[2]
    p = a[3]
    physical = Memory (a[0], '/tmp/ep3.mem', s) 
    virtual = Memory (a[1], '/tmp/ep3.vir', s) 
    pq = ut.ProcessQueue ()
    rq = ut.RunningQueue ()
    proc = ut.Process (file.readline ().split ())
    time = 0
    while True:
        while proc != None and proc.t0 == time:
            pq.push (proc)
            rq.push (proc)
            proc.base = virtual.insert (proc, m_alg) #base limite, mapear a pagina, cuida aqui
            atr = file.readline ().split ()
            if atr != []:
                proc = ut.Process (atr)
            else:
                proc = None

        while pq.get_size () > 0 and pq.top ().next_time () == time:
            ac_proc = pq.top ()
            ac_pos = ac_proc.next_pos ()
            #algoritmo de pagina
            pq.pop ()

        while rq.get_size () > 0 and rq.top ().tf == time:
            virtual.remove (rq.top ())
            rq.pop ()
        
        #TODO, ta feio
        if time % inter == 0:
            virtual.show ()
        #    physical.show ()

        if proc == None and rq.get_size () == 0:
            break

        time += 1
    file.close ()
