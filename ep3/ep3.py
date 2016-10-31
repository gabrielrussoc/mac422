f = None
s = None
e = None

while True:
    line = raw_input('(ep3): ')
    if line == 'sai':
        break
    line = line.split (" ")
    if line[0] == 'carrega':
        if len (line) != 2:
            print 'Uso: carrega <arquivo>'
        else:
            f = line[1]
            print "Carregando arquivo" + line[1]
    elif line[0] == 'espaco':
        if len (line) != 2:
            print 'Uso: espaco <num>'
        else:
            e = line[1]
            print 'Algorimo de espaco:' + line[1]
    elif line[0] == 'substitui':
        if len (line) != 2:
            print 'Uso: substitui <num>'
        else:
            s = line[1]
            print 'Algoritmo de substituicao:' + line[1]
    elif line[0] == 'executa':
        if len (line) != 3:
            print 'Uso: executa <intervalo>'
        elif f is None:
            print 'Erro: Arquivo de entrada nao definido'
        elif s is None:
            print 'Erro: Algoritmo de espaco nao definido'
        elif e is None:
            print 'Erro: Algoritmo de substituicao nao definido'
        else:
            print 'Executa a simulacao e imprime intervalo:' + line[1] + ':' + line[2]
    else:
        print 'Comando nao encontrado'
