import utility as ut
from bitarray import bitarray
import math

class Memory:
    def __init__ (self, size, file, s, p):
        self.size = size
        self.file = open (file, 'w+b')
        self.write (0, int (size / s), -1)
        self.s = s
        self.p = p
        self.bitmap = int (size / p) * bitarray ('0')
        self.counter = -1

    def __del__ (self):
        self.file.close ()
        
    #Cada linha represeta um bloco de tamanho s
    def write (self, block, quantity, value):
        self.file.seek (block * ut.INT_BYTES)
        for i in range (quantity):
            self.file.write (value.to_bytes (ut.INT_BYTES, byteorder = 'big', signed = True))

    def read (self, block):
        self.file.seek (block * ut.INT_BYTES)
        return int.from_bytes (self.file.read (ut.INT_BYTES), byteorder = 'big', signed = True) 

    #Retorna a pagina inicial do processo
    def insert (self, process, algorithm):
        p_size = math.ceil (process.size / self.p)
        if algorithm == 1:
            return self.first_fit (process.pid, p_size)
        elif algorithm == 2:
            return self.next_fit (process.pid, p_size)
        elif algorithm == 3:
            return self.best_fit (process.pid, p_size)
        else:
            return self.worst_fit (process.pid, p_size)

    def remove (self, process):
        base = process.base
        p_size = math.ceil (process.size / self.p)
        self.bitmap[base : base + p_size] = p_size * bitarray ('0') 
        self.write (base * int (self.p / self.s), p_size * int (self.p / self.s), -1)

    def show (self):
        for i in range (int (self.size / self.s)):
            print (str (i) + ': ' + str (self.read (i)))

    #p_size eh a quantidade de paginas do processo
    def first_fit (self, pid, p_size):
        arr = p_size * bitarray ('0')
        for i in range (len (self.bitmap) - p_size + 1):
            if self.bitmap[i : i + p_size] == arr:
                self.write (i * int (self.p / self.s), p_size * int (self.p / self.s), pid)
                self.bitmap[i : i + p_size] = p_size * bitarray ('1')
                return i
                
    
    def next_fit (self, pid, p_size):
        arr = p_size * bitarray ('0')
        i = self.counter + 1
        while (i != self.counter):
            if i > len (self.bitmap) - p_size:
                i = 0
            if self.bitmap[i : i + p_size] == arr:
                self.write (i * int (self.p / self.s), p_size * int (self.p / self.s), pid)
                self.bitmap[i : i + p_size] = p_size * bitarray ('1')
                self.counter = i + p_size - 1
                return i
            i += 1
    
    def best_fit (self, pid, p_size):
        best_pos = 0
        best_size = len (self.bitmap)
        i = 0
        
        for j in range (len (self.bitmap)):
            if self.bitmap[j]:
                if j - i < best_size and j - i >= p_size:
                    best_size = j - i
                    best_pos = i
                i = j + 1

        j = len (self.bitmap)
        if j - i < best_size and j - i >= p_size:
            best_size = j - i
            best_pos = i

        self.write (best_pos * int (self.p / self.s), p_size * int (self.p / self.s), pid)
        self.bitmap[best_pos : best_pos + p_size] = p_size * bitarray ('1')
        return best_pos
    
    def worst_fit (self, pid, p_size):
        worst_pos = 0
        worst_size = 0
        i = 0
        
        for j in range (len (self.bitmap)):
            if self.bitmap[j]:
                if j - i > worst_size and j - i >= p_size:
                    worst_size = j - i
                    worst_pos = i
                i = j + 1
        
        j = len (self.bitmap)
        if j - i > worst_size and j - i >= p_size:
            worst_size = j - i
            worst_pos = i

        self.write (worst_pos * int (self.p / self.s), p_size * int (self.p / self.s), pid)
        self.bitmap[worst_pos : worst_pos + p_size] = p_size * bitarray ('1')
        return worst_pos 

