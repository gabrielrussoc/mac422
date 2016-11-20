# EP3 de MAC0422
# Professor Daniel Batista
# 2016 IME - USP
# Gabriel de Russo e Carmo 9298041
# Victor Wichmann Raposo 9298020
from memory import Memory
from pages import Pages
import utility as ut
import math

# Modulo responsavel pela execucao e simulacao do trace e dos algoritmos

# Recebe um arquivo de trace e devolve um vetor com
# todos os processos do arquivo
def load (trace):
    ret = []
    for line in trace:
        if line.strip () == '':
            continue
        ret.append (ut.Process (line.split ()))
    return ret

# Recebe um vetor de processos timeline e imprime uma tabela relacionando
# o nome do processo com seu pid
def show_pids (timeline):
    print ('\n' + 10 * '-')
    print ('PROCESSO: PID\n')
    for proc in timeline:
        print (proc.name + ': ' + str (proc.pid))
    print (10 * '-' + '\n')

# Simula o arquivo de trace com algoritmo de memoria m_alg
# e de substituicao de pagina p_alg. Imprime o status das memorias
# na tela de acordo com o intervalo inter
def run (trace, m_alg, p_alg, inter):
    #Entrada: total virtual s p
    a = list (map (int, trace.readline ().split ()))
    s = int (a[2])
    p = int (a[3])
    
    # Inicializando estruturas e variaveis auxiliares
    physical = Memory (a[0], '/tmp/ep3.mem', s, p) 
    virtual = Memory (a[1], '/tmp/ep3.vir', s, p) 
    pq = ut.ProcessQueue ()
    rq = ut.RunningQueue ()
    time = index = 0
    timeline = load (trace)
    pgt = Pages (physical, virtual, p_alg)
    zero_r = 32

    show_pids (timeline)

    while True:
        # Chegada de processos
        while index < len (timeline) and timeline[index].t0 == time:
            proc = timeline[index]
            if len (proc.access[0]) > 0:
                pq.push (proc)
            rq.push (proc)
            proc.base = virtual.insert (proc, m_alg)
            index += 1

        # Acesso da memoria fisica
        while pq.get_size () > 0 and pq.top ().next_time () == time:
            ac_proc = pq.top ()
            pgt.access (ac_proc) 
            pq.pop ()

        # Saida de processos
        while rq.get_size () > 0 and rq.top ().tf == time:
            proc = rq.top ()
            virtual.remove (proc)
            pgt.remove (proc)
            rq.pop ()
        
        # Relatorio
        if time % inter == 0:
            print ('Instante ' + str (time) + '\n')
            print ('Memoria virtual')
            virtual.show ()
            print ()
            print ('Memoria fisica')
            physical.show ()
            print (20 * '-' + '\n')
        
        if time % zero_r == 0:
            pgt.reset_r ()

        # Nao ha mais acessos a memoria nem chegada de processos
        if index == len (timeline) and rq.get_size () == 0:
            break

        time += 1
    
    print ('Tempo gasto alocando memória: ' + str (ut.aloc_time) + 's')
    print ('Falhas de página: ' + str (ut.page_fault_counter))

