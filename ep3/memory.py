import utility as ut
from bitarray import bitarray
import math

# Modulo responsavel pela representacao e manipulacao das memorias

class Memory:
    # Construtor
    def __init__ (self, size, file, s, p):
        self.size = size
        self.file = open (file, 'w+b')
        self.write (0, size, -1)
        self.s = s
        self.p = p
        self.bitmap = int (size / p) * bitarray ('0')
        self.counter = -1

    # Destrutor
    def __del__ (self):
        self.file.close ()
        
    # Recebe uma posicao inicial pos, uma quantidade quantity de posicoes e um valor value. Escreve no arquivo binario 
    # a quantidade de posicoes a partir da posicao inical o valor dado
    def write (self, pos, quantity, value):
        self.file.seek (pos * ut.INT_BYTES)
        for i in range (quantity):
            self.file.write (value.to_bytes (ut.INT_BYTES, byteorder = 'big', signed = True))

    # Recebe uma posicao pos do arquivo binario e devolve o conteudo dessa posicao
    def read (self, pos):
        self.file.seek (pos * ut.INT_BYTES)
        return int.from_bytes (self.file.read (ut.INT_BYTES), byteorder = 'big', signed = True) 

    # Recebe um processo e um codigo de um algoritmo de gerencia de espaco livre, insere o processo na memoria
    # e devolve a pagina inicial em que ele esta contido
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

    # Recebe um processo e remove-o da memoria, atribuindo o valor -1, no arquivo binario, 
    # para as posicoes de memoria que ele estava contido
    def remove (self, process):
        base = process.base
        p_size = math.ceil (process.size / self.p)
        self.bitmap[base : base + p_size] = p_size * bitarray ('0') 
        self.write (base * self.p, p_size * self.p, -1)

    # Imprime o estado da memoria
    def show (self):
        for i in range (0, int (self.size)):
            print (str (i) + ': ' + str (self.read (i)))


    # Recebe um id de um processo, pid, e o tamanho (quantidade de paginas) desse processo, p_size.
    # Insere ele na memoria usando o algoritmo first fit e devolve a pagina inicial que o processo ocupa
    def first_fit (self, pid, p_size):
        arr = p_size * bitarray ('0')
        for i in range (len (self.bitmap) - p_size + 1):
            if self.bitmap[i : i + p_size] == arr:
                self.write (i * self.p, p_size * self.p, pid)
                self.bitmap[i : i + p_size] = p_size * bitarray ('1')
                return i
                
    
    # Recebe um id de um processo, pid, e o tamanho (quantidade de paginas) desse processo, p_size.
    # Insere ele na memoria usando o algoritmo next fit e devolve a pagina inicial que o processo ocupa
    def next_fit (self, pid, p_size):
        arr = p_size * bitarray ('0')
        i = self.counter + 1
        while (i != self.counter):
            if i > len (self.bitmap) - p_size:
                i = 0
            if self.bitmap[i : i + p_size] == arr:
                self.write (i * self.p, p_size * self.p, pid)
                self.bitmap[i : i + p_size] = p_size * bitarray ('1')
                self.counter = i + p_size - 1
                return i
            i += 1
    
    # Recebe um id de um processo, pid, e o tamanho (quantidade de paginas) desse processo, p_size.
    # Insere ele na memoria usando o algoritmo best fit e devolve a pagina inicial que o processo ocupa
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

        self.write (best_pos * self.p, p_size * self.p, pid)
        self.bitmap[best_pos : best_pos + p_size] = p_size * bitarray ('1')
        return best_pos
    
    # Recebe um id de um processo, pid, e o tamanho (quantidade de paginas) desse processo, p_size.
    # Insere ele na memoria usando o algoritmo worst fit e devolve a pagina inicial que o processo ocupa
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

        self.write (worst_pos * self.p, p_size * self.p, pid)
        self.bitmap[worst_pos : worst_pos + p_size] = p_size * bitarray ('1')
        return worst_pos 

