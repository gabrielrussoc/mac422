# Gerador de arquivos de trace
# Cortesia de Marcos Pontes, grande astronauta

import sys
import random
import array
import math

# A interpretacao dos seguintes parametros pode estar equivocada
s_total = 100 # Valor maximo para unidade de alocacao
p_total = 100 # Valor maximo para tamanho da pagina
l_total = 1000 # ?
v_total = 1000 # Valor maximo para memoria virtual
t_final = 10000 # Tempo final maximo

f = open('in', 'w')

s = random.randint(1, s_total)
p = random.randint(1, p_total) * s
virtual = random.randint(2, v_total) * p
total = random.randint(1, virtual / p / 2) * p
size = random.randint(1, 100)

f.write(str(total) + ' ' + str(virtual) + ' ' + str(s) + ' ' + str(p) + '\n')

tant = 0
sm = 0
for i in range(0, size):
	t0 = random.randint(tant, t_final)
	tf = random.randint(t0, t_final * 2)
	sz = random.randint(0, min(tf - t0, 100))
	nome = 'processo' + str(i + 1)
	b = random.randint(2, int(virtual / size))
	if (math.ceil(b/p) * p > virtual / size):
		b = b - p
	sm = sm + math.ceil(b / p) * p
	f.write(str(t0) + ' ' + nome + ' ' + str(tf) + ' ' + str(b))
	ti = []
	pi = []
	for k in range(0, sz):
		pi.append(random.randint(1, b - 1))
		ti.append(random.randint(t0, tf))
	ti.sort()
	for k in range(0, sz):
		f.write(' ' + str(pi[k]) + ' ' + str(ti[k]))
	f.write('\n')
	tant = t0;
f.close()
#if (virtual < sm):
#	print("Deu bosta " + str(virtual) + ' < ' + str(sm))





