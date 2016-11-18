#!/usr/local/bin/python3
import execution as ex
import readline

readline.parse_and_bind('tab: complete')

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
            try:
                f = open (line[1])
            except FileNotFoundError:
                print ('Arquivo não encontrado!')
    elif line[0] == 'espaco':
        if len (line) != 2:
            print ('Uso: espaco <algoritmo>')
        else:
            e = line[1]
    elif line[0] == 'substitui':
        if len (line) != 2:
            print ('Uso: substitui <algoritmo>')
        else:
            s = line[1]
    elif line[0] == 'executa':
        if len (line) != 2:
            print ('Uso: executa <intervalo>')
        else:
            it = line[1]
            ex.run (f, int (e), int (s), int (it))
    else:
        print ('Comando nao encontrado')
