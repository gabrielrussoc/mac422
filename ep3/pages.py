import memory
from bitarray import bitarray

class Pages:
    def __init__ (self, physical, virtual, p_alg):
        self.physical = physical
        self.virtual = virtual
        self.size = int (virtual.size / virtual.p)
        self.p_alg = p_alg
        self.present = bitarray ('0') * self.size 
        self.reset_r ()

    def decode (self, base, pos):
        return base + int (pos / self.physical.p) 

    def access (self, proc):
        pos = proc.next_pos ()
        page = decode (proc.base, pos)
        if not self.present[page]:
            page_fix (page)
        self.r[page] = 1;

    def page_fix (self, page):
        a = p_alg
        if a == 1:
            ...
        elif a == 2:
            ...
        elif a == 3:
            ...
        else:
            ...

    def reset_r (self):
        self.r = bitarray ('0') * self.size

    def optimal_init (self, timeline):
        self.optimal_counter = [0] * self.size
        for proc in timeline:
            for ac in proc.access[0]:
                self.optimal_counter[self.decode (proc.base, ac)] += 1

    def optimal (self):
        ...

    def second_chance (self):
        ...

    def clock (self):
        ...

    def lru (self):
        ...

