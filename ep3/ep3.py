while True:
    line = raw_input('(ep3): ')
    if line == 'sai':
        break
    line = line.split (" ")
    if line[0] == 'carrega':
        if len (line) != 2:
            print 'Uso: carrega <arquivo>'
        else:
            print "Carregando arquivo" + line[1]
    elif line[0] == 'espaco':
        if len (line) != 2:
            print 'Uso: espaco <num>'
        else:
            print 'Algorimo de espaco:' + line[1]
    elif line[0] == 'substitui':
        if len (line) != 2:
            print 'Uso: substitui <num>'
        else:
            print 'Algoritmo de substituicao:' + line[1]
    elif line[0] == 'executa':
        if len (line) != 3:
            print 'Uso: executa <intervalo>'
        else:
            print 'Executa a simulacao e imprime intervalo:' + line[1] + ':' + line[2]
