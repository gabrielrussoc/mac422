import memory
import math
from bitarray import bitarray
from queue import Queue
import utility as ut

# Modulo responsavel pela gerencia das paginas e dos quadros de paginas

class Pages:
    # Construtor
    def __init__ (self, physical, virtual, p_alg):
        self.physical = physical
        self.virtual = virtual
        self.p = virtual.p
        self.size = int (virtual.size / self.p)
        self.frame_size = int (physical.size / physical.p)
        self.p_alg = p_alg
        self.where = [-1] * self.size
        self.r = bitarray ('0') * self.size

        # Posicao fantasma, usada para inicializar as estruturas
        self.where.append (-1)
        self.r.append (bitarray ('0'))

        self.alg_init ()

    # Recebe uma base e uma posicao relativa de memoria e devolve
    # a pagina correspondente
    def decode (self, base, pos):
        return base + int (pos / self.p) 

    # Simula o acesso do processo proc a memoria
    def access (self, proc):
        # Cada acesso atualiza a estrutura da LRU
        if self.p_alg == 4:
            self.lru_update ()
        pos = proc.next_pos ()
        page = self.decode (proc.base, pos)
        if self.where[page] == -1:
            self.page_fix (proc)
        self.r[page] = 1

    # Trata o caso de page fault de um processo proc de acordo
    # com o algoritmo determinado
    def page_fix (self, proc):
        ut.debug ('Page fault!')
        a = self.p_alg
        if a == 1:
            self.optimal (proc)
        elif a == 2:
            self.second_chance (proc)
        elif a == 3:
            self.clock (proc)
        else:
            self.lru (proc)

    # Iniciliza a estrutura do algoritmo de substituicao de paginas
    def alg_init (self):
        a = self.p_alg
        if a == 1:
            self.optimal_init ()
        elif a == 2:
            self.second_chance_init ()
        elif a == 3:
            self.clock_init ()
        else:
            self.lru_init ()

    # Remove todas as informacoes relacionadas as paginas do processo proc
    def remove (self, proc):
        p_size = math.ceil (proc.size / self.p)
        for page in range (proc.base, proc.base + p_size, self.p):
            if self.where[page] != -1:
                loc = self.where[page]
                self.where[page] = -1
                self.physical.write (loc * self.p, self.p, -1)
                self.physical.bitmap[loc * self.p : loc * self.p + self.p] = bitarray ('0') * self.p
        self.r[proc.base : proc.base + p_size] = bitarray ('0') * p_size
    
    # Reseta o bit R de todas as paginas
    def reset_r (self):
        self.r = bitarray ('0') * (self.size + 1)

    # Iniciliza a estrutura utilizada no algoritmo optimal
    def optimal_init (self):
        self.label = [(self.size, math.inf)] * self.frame_size

    # Iniciliza a estrutura utilizada no algoritmo second chance
    def second_chance_init (self):
        self.queue = Queue ()
        for i in range (self.frame_size):
            # fila de pair (pagina, page frame)
            self.queue.put ((self.size, i))

    # Iniciliza a estrutura utilizada no algoritmo clock
    def clock_init (self):
        self.clk = []
        for i in range (self.frame_size):
            self.clk.append ((self.size, i))
        self.it = 0
    
    # Iniciliza a estrutura utilizada no algoritmo LRU
    def lru_init (self):
        self.page_counter = []
        for i in range (self.frame_size):
            self.page_counter.append ((self.size, 0))

    # Insere a proxima pagina acessada do processo proc
    # no quadro de paginas de acordo com o algoritmo optimal
    def optimal (self, proc):
        n_page = self.decode (proc.base, proc.next_pos ())
        opt = -1
        frame = -1
        for i in range (self.frame_size):
            page, label = self.label[i]
            if label > opt:
                opt = label
                frame = i
        page, label = self.label[frame]
        self.where[page] = -1
        self.r[page] = 0
        self.where[n_page] = frame
        self.physical.write (frame * self.p, self.p, proc.pid)
        self.physical.bitmap[frame * self.p : frame * self.p + self.p] = bitarray ('1') * self.p
        self.label[frame] = (n_page, proc.next_next_time ())

    # Insere a proxima pagina acessada do processo proc
    # no quadro de paginas de acordo com o algoritmo second chance
    def second_chance (self, proc):
        n_page = self.decode (proc.base, proc.next_pos ())
        while True:
            page, frame = self.queue.get ()
            if not self.r[page]:
                # Insere
                self.queue.put ((n_page, frame))
                self.where[n_page] = frame
                self.physical.write (frame * self.p, self.p, proc.pid)
                self.physical.bitmap[frame * self.p : frame * self.p + self.p] = bitarray ('1') * self.p
                # Remove
                self.where[page] = -1
                self.r[page] = 0
                break
            else:
                self.r[page] = 0
                self.queue.put ((page, frame))
    
    # Insere a proxima pagina acessada do processo proc
    # no quadro de paginas de acordo com o algoritmo clock
    def clock (self, proc):
        n_page = self.decode (proc.base, proc.next_pos ())
        while True:
            page, frame = self.clk[self.it]
            if not self.r[page]:
                # Insere
                self.clk[self.it] = (n_page, frame)
                self.where[page] = frame
                self.physical.write (frame * self.p, self.p, proc.pid)
                self.physical.bitmap[frame * self.p : frame * self.p + self.p] = bitarray ('1') * self.p
                # Remove
                self.where[page] = -1
                self.r[page] = 0
                self.it = (self.it + 1) % len (self.clk)
                break
            else:
                self.r[page] = 0
                self.it = (self.it + 1) % len (self.clk)

    # Insere a proxima pagina acessada do processo proc
    # no quadro de paginas de acordo com o algoritmo LRU
    def lru (self, proc):
        n_page = self.decode (proc.base, proc.next_pos ())
        best = math.inf 
        frame = -1
        for i in range (self.frame_size):
            page, counter = self.page_counter[i]
            if counter < best:
                counter = best
                frame = i
        page = self.page_counter[frame][0]
        self.where[page] = -1
        self.r[page] = 0
        self.page_counter[frame] = (n_page, 0)
        self.where[n_page] = frame
        self.physical.write (frame * self.p, self.p, proc.pid)
        self.physical.bitmap[frame * self.p : frame * self.p + self.p] = bitarray ('1') * self.p

    # Atualiza os contadores do algoritmo LRU
    def lru_update (self):
        for i in range (frame_size):
            page, counter = self.page_counter[i]
            self.page_counter[i] = (page, (i >> 1) + (int (self.r[page]) << ((8 * ut.INT_BYTES) - 1)))

