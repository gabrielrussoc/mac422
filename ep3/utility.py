import heapq
import math

# Modulo de funcoes e classes utilitarias

# Variaveis globais
INT_BYTES = 4
DEBUG = False #modo debug
aloc_time = 0 #contagem do tempo de alocacao
page_fault_counter = 0 #contagem de page faults

# Imprime apenas quando a variavel global DEBUG = true
def debug (s):
    if DEBUG:
        print (s)

class Process:
    pid_count = 0
    
    # Construtor
    def __init__ (self, atr):
        # Entrada: t0 nome tf b p1 t1 ... pn tn

        self.t0 = int (atr[0])
        self.pid = Process.pid_count
        self.name = atr[1]
        self.tf = int (atr[2])
        self.base = 0
        self.size = int (atr[3])
        self.access = [[], []]
        for i in range (4, len (atr), 2):
            self.access[0].append (int (atr[i])) # posicoes
            self.access[1].append (int (atr[i+1])) # instantes

        # Iterador do vetor de acessos
        self.access_it = 0

        Process.pid_count += 1

    # Devolve a proxima posicao que sera acessada
    def next_pos (self):
        return self.access[0][self.access_it]

    # Devolve o proximo instante que ocorrera um acesso
    def next_time (self):
        return self.access[1][self.access_it]
    
# Heap de processos ordenados em relacao ao tempo de acesso de memoria
class ProcessQueue:
    
    # Definido uma classe com o comparable entre processos desejado
    class Item:
        def __init__ (self, proc):
            self.proc = proc

        def __lt__ (self, other):
            i = self.proc.access_it
            j = other.proc.access_it
            return self.proc.access[1][i] < other.proc.access[1][j]
        
        def __eq__ (self, other):
            i = self.proc.access_it
            j = other.proc.access_it
            return self.proc.access[1][i] == other.proc.access[1][j]

    # Construtor
    def __init__ (self):
        self.heap = []
        self.size = 0

    # Devolve a quantidade de elementos na estrutura
    def get_size (self):
        return self.size

    # Recebe um processo proc e insere-o na estrutura
    def push (self, proc):
        heapq.heappush (self.heap, self.Item (proc))
        self.size += 1

    # Devolve o menor elemento da esturutra, devolve None caso ela esteja vazia
    def top (self):
        if self.size == 0:
            return None
        return self.heap[0].proc

    # Deleta o menor elemento da estrutura, devolve None caso ela esteja vazia
    def pop (self):
        if self.size == 0:
            return None
        proc = heapq.heappop (self.heap).proc
        self.size -= 1
        proc.access_it += 1
        if proc.access_it != len (proc.access[1]):
            self.push (proc)

# Heap de processos ordenados em relacao ao tempo final
class RunningQueue:

    # Definido uma classe com o comparable entre processos desejado
    class Item:
        def __init__ (self, proc):
            self.proc = proc

        def __lt__ (self, other):
            i = self.proc.tf
            j = other.proc.tf
            return i < j

        def __eq__ (self, other):
            i = self.proc.tf
            j = other.proc.tf
            return i == j

    # Construtor
    def __init__ (self):
        self.heap = []
        self.size = 0

    # Devolve a quantidade de elementos na estrutura
    def get_size (self):
        return self.size

    # Recebe um processo proc e insere-o na estrutura
    def push (self, proc):
        heapq.heappush (self.heap, self.Item (proc))
        self.size += 1

    # Devolve o menor elemento da esturutra, devolve None caso ela esteja vazia
    def top (self):
        if self.size == 0:
            return None
        return self.heap[0].proc

    # Deleta o menor elemento da estrutura, devolve None caso ela esteja vazia
    def pop (self):
        if self.size == 0:
            return None
        proc = heapq.heappop (self.heap).proc
        self.size -= 1

'''unit test
a = Process (['0', 'procA', '10', '3', '1', '3', '3', '5'])
b = Process (['0', 'procB', '100', '3', '1', '3', '3', '1'])

pq = ProcessQueue ()
pq.push (a)
pq.push (b)

print (pid_name[pq.top ().pid])
pq.pop ()
print (pid_name[pq.top ().pid])
pq.pop ()
print (pid_name[pq.top ().pid])
pq.pop ()
print (pid_name[pq.top ().pid])
pq.pop ()
pq.pop ()

print (10 * '-')

rq = RunningQueue ()
rq.push (a)
rq.push (b)
print (pid_name[rq.top ().pid])
rq.pop ()
print (pid_name[rq.top ().pid])
rq.pop ()
rq.pop ()
'''
