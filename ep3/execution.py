import memory as mem
import utility as ut
import math

def init (f):
    a = f.readline ().split (' ');
    fisica = mem.Memory (a[0] , '/tmp/ep3.mem') 
    virtual = mem.Memory (a[1] , '/tmp/ep3.vir') 
    s = a[2]
    p = a[3]
    bitmap = [False] * a[1] / s;

def run (f, algM, algP):
    fo = open (f, "r");
    time = 0
    init (fo)
    proc = ut.Process (fo)
    # le as variaveis globais 
    while ():
        while proc.t0 == time:
           virtual.insert (Math.ceil (proc.b / s), proc.name, algP)
           #insere no vetor de pripridadde
           proc = Process (fo)
        time += 1
    fo.close ()
