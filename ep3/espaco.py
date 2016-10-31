def first_fit (p_size):
    arr = [False] * p_size
    for i in range (0, len (bitmap)-p_size):
        if bitmap[i:i+p_size] == arr:
            #insere no arquivo 
            bitmap[i:i+p_size] = [True] * p_size
            break;

def next_fit (p_size):
    arr = [False] * p_size
    i = next_fit.counter + 1
    while (i != next_fit.counter):
        if i > len (bitmap) - p_size:
            i = 0
        if bitmap[i:i+p_size] == arr:
            #insere no arquivo 
            bitmap[i:i+p_size] = [True] * p_size
            next_fit.counter = i + p_size - 1
            break;
        i += 1

def best_fit (p_size):
    best_pos = 0
    block_size = 0
    pos = -1
    size = 0
    
    for i in range (0, len (bitmap)):
        if bitmap[i] and pos == -1:
            size = 0
            pos = i
        if not bitmap[i]:
            if size > p_size && size < block_size:
                block_size = size
                best_pos = pos
            pos = -1
        size += 1

    #insere no arquivo 

def worst_fit (p_size):
    worst_pos = 0
    block_size = 0
    pos = -1
    size = 0
    
    for i in range (0, len (bitmap)):
        if bitmap[i] and pos == -1:
            size = 0
            pos = i
        if not bitmap[i]:
            if size > p_size && size > block_size:
                block_size = size
                best_pos = pos
            pos = -1
        size += 1

    #insere no arquivo 
