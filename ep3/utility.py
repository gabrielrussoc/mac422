INT_BYTES = 4
running = 0
pid_count = 0
pid_name = []

class Process:
    def __init__ (self, atr):
        self.t0 = int (atr[0])
        global pid_count
        self.pid = pid_count
        pid_name.append (atr[1])
        pid_count += 1
        self.tf = int (atr[2])
        self.size = int (atr[3])
        self.access = [[], []]
        for i in range (4, len (atr), 2):
            self.access[0].append (int (atr[i]))
            self.access[1].append (int (atr[i+1]))


