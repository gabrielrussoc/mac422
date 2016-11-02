#!/usr/bin/python3
import execution as ex

f = None
s = None
e = None
it = None

while True:
    line = input ('(ep3): ')
    if line == 'sai':
        break
    line = line.split ()
    if line[0] == 'carrega':
        if len (line) != 2:
            print ('Uso: carrega <arquivo>')
        else:
            f = line[1]
            print ('Carregando arquivo: ' + line[1])
    elif line[0] == 'espaco':
        if len (line) != 2:
            print ('Uso: espaco <num>')
        else:
            e = line[1]
            print ('Algorimo de espaco:' + line[1])
    elif line[0] == 'substitui':
        if len (line) != 2:
            print ('Uso: substitui <num>')
        else:
            s = line[1]
            print ('Algoritmo de substituicao:' + line[1])
    elif line[0] == 'executa':
        if len (line) != 2:
            print ('Uso: executa <intervalo>')
        elif f is None:
            print ('Erro: Arquivo de entrada nao definido')
        elif e is None:
            print ('Erro: Algoritmo de espaco nao definido')
        elif s is None:
            print ('Erro: Algoritmo de substituicao nao definido')
        else:
            it = line[1]
            print ('Executa a simulacao e imprime intervalo:' + line[1])
            ex.run (f, int (e), int (s), int (it))
    else:
        print ('Comando nao encontrado')
