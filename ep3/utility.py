import heapq

INT_BYTES = 4
running = 0
pid_name = []

class Process:
    pid_count = 0
    

    #atr eh uma lista de strings
    #t0 nome tf b p1 t1 ... pn tn
    def __init__ (self, atr):
        self.t0 = int (atr[0])
        self.pid = Process.pid_count
        pid_name.append (atr[1])
        Process.pid_count += 1
        self.tf = int (atr[2])
        self.base = 0
        self.size = int (atr[3])
        self.access = [[], []]
        self.access_it = 0
        for i in range (4, len (atr), 2):
            self.access[0].append (int (atr[i]))
            self.access[1].append (int (atr[i+1]))

    def next_pos (self):
        return self.access[0][self.access_it]

    def next_time (self):
        return self.access[1][self.access_it]


class ProcessQueue:
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

    def __init__ (self):
        self.heap = []
        self.size = 0

    def get_size (self):
        return self.size

    def push (self, proc):
        heapq.heappush (self.heap, self.Item (proc))
        self.size += 1

    def top (self):
        if self.size == 0:
            return None
        return self.heap[0].proc

    def pop (self):
        if self.size == 0:
            return None
        proc = heapq.heappop (self.heap).proc
        self.size -= 1
        proc.access_it += 1
        if proc.access_it != len (proc.access[1]):
            self.push (proc)

class RunningQueue:
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

    def __init__ (self):
        self.heap = []
        self.size = 0

    def get_size (self):
        return self.size

    def push (self, proc):
        heapq.heappush (self.heap, self.Item (proc))
        self.size += 1

    def top (self):
        if self.size == 0:
            return None
        return self.heap[0].proc

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
