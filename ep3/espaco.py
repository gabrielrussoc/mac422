def first_fit (p_size):
    arr = [0] * p_size
    for i in bitmap:
        if bitmap[i:i+p_size] == arr:
            #insere no arquivo 
            bitmap[i:i+p_size] = [1] * p_size
            break;


            
