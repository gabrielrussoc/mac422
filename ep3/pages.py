import memory
from bitarray import bitarray
from queue import Queue

class Pages:
    def __init__ (self, physical, virtual, p_alg, timeline):
        self.physical = physical
        self.virtual = virtual
        self.p = virtual.p
        self.size = int (virtual.size / self.p)
        self.p_alg = p_alg
        self.present = bitarray ('0') * self.size
        self.reset_r ()

        # Posicao fantasma, usada para inicializar as estruturas
        self.present.append (bitarray ('0'))
        self.r.append (bitarray ('0'))

        self.alg_init (timeline)

    def decode (self, base, pos):
        return base + int (pos / self.p) 

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

    def second_chance_init (self):
        size = int (self.physical.size / self.physical.p)
        self.queue = Queue ()
        for i in range (size):
            # fila de pair (posicao na tabela de paginas, posicao na memfisica)
            self.queue.put ([self.size, i])

    def clock_init (self):
        size = int (self.physical.size / self.physical.p)
        self.clk = []
        for i in range (size):
            self.clk.append ([self.size, i])
        self.it = 0
        

        

    def optimal (self):
        ...

    def second_chance (self, page):
        while True:
            frame = self.queue.get ()
            if not self.r[frame[0]]]: 

                # Insere
                self.queue.put ([page, frame[1]])
                self.r[page] = 1
                self.present[page] = 1
                    # obter pid da page
                self.physical.write (frame[1] * self.p, pid)

                # Remove
                self.present[frame[0]] = 0
                self.r[frame[0]] = 0

                break;
            else:
                self.r[frame[0]] = 0
                self.queue.put (frame)
        

    def clock (self, page):
        while True:
            frame = self.clk[self.it]
            if not self.r[frame[0]]:
                # Insere
                self.clk[self.it][0] = page
                self.r[page] = 1
                self.present[page] = 1
                    # obter pid da page
                self.physical.write (frame[1] * self.p, pid
                
                # Remove
                self.present[frame[0]] = 0
                self.r[frame[0]] = 0

                self.it = (self.it + 1) % self.size

                break
            else:
                self.r[frame[0]] = 0
                self.it = (self.it + 1) % self.size

    def lru (self):
        ...

