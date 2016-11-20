# EP3 de MAC0422
# Professor Daniel Batista
# 2016 IME - USP
# Gabriel de Russo e Carmo 9298041
# Victor Wichmann Raposo 9298020
import execution as ex
import readline

# Modulo do shell

readline.parse_and_bind('tab: complete')

trace = None
alg_sub = None
alg_esp = None
inter = None

espaco = {1: 'First fit', 2: 'Next fit', 3: 'Best fit', 4: 'Worst fit'}
subs = {1: 'Optimal', 2: 'Second chance', 3: 'Clock', 4: 'Least Recently Used'}

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
                trace = open (line[1])
            except FileNotFoundError:
                print ('Arquivo não encontrado!')
    elif line[0] == 'espaco':
        if len (line) != 2:
            print ('Uso: espaco <algoritmo>')
        else:
            alg_esp = int (line[1])
    elif line[0] == 'substitui':
        if len (line) != 2:
            print ('Uso: substitui <algoritmo>')
        else:
            alg_sub = int (line[1])
    elif line[0] == 'executa':
        if len (line) != 2:
            print ('Uso: executa <intervalo>')
        else:
            inter = int (line[1])
            print ('Iniciando simulação...')
            print ('Algoritmo de gerência de espaço livre: ' + str (alg_esp) + ' - ' + espaco[alg_esp])
            print ('Algoritmo de substiução de páginas: ' + str (alg_sub) + ' - ' + subs[alg_sub])
            ex.run (trace, alg_esp, alg_sub, inter)
    else:
        print ('Comando nao encontrado')

