INT_BYTES = 4

class Process:
    def __init__ (f):
        a = f.readline ().split (' ');
        self.t0 = a[0]
        self.name = a[1] 
        self.tf = a[2]
        self.b = a[3]
        for i in range (4, len (a), 2):
            self.access = append([a[i], a[i+1]])

