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
        if bitmap[i:i+p_size] == arr:
            #insere no arquivo 
            bitmap[i:i+p_size] = [True] * p_size
            next_fit.counter = i + p_size - 1
            break;

        

def best_fit (p_size):

            
