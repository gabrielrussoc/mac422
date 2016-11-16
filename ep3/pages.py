import memory
from bitarray import bitarray
from queue import Queue

class Pages:
    def __init__ (self, physical, virtual, p_alg, timeline):
        self.physical = physical
        self.virtual = virtual
        self.size = int (virtual.size / virtual.p)
        self.p_alg = p_alg
        
        # Vetor que marca a posicao da memoria fisica se esta presente e -1 c.c
        self.present = [-1] * self.size 
        self.reset_r ()
        self.alg_init (timeline)

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
            second_chance ()
        elif a == 3:
            ...
        else:
            ...

    def alg_init (self, timeline):
        a = p_alg
        if a == 1:
            optimal_init (timeline)
        elif a == 2:
            second_chance_init (timeline)
        elif a == 3:
            ...
        else:

    def reset_r (self):
        self.r = bitarray ('0') * self.size

    def optimal_init (self, timeline):
        self.optimal_counter = [0] * self.size
        for proc in timeline:
            for ac in proc.access[0]:
                self.optimal_counter[self.decode (proc.base, ac)] += 1

    def second_chance_init (self, timeline):
        size = int (self.physical.size / self.physical.p)
        self.queue = Queue ()
        for i in range (size):
            self.queue.put (i)

    def optimal (self):
        ...

    def second_chance (self, page):
        while True:
            frame = self.queue.get ()
            if not self.r[frame]: 

                # Insere
                self.queue.put (page)
                self.r[page] = 1
                self.present[page] = self.present[frame]
                physical.write (self.present[page] * self.pysh

                # Remove
                self.present[frame] = -1
                

        

    def clock (self):
        ...

    def lru (self):
        ...

