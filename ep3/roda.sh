#!/bin/zsh

# Parametros da linha de comando
# Caso de teste $1
# Algoritmo de gerencia de memoria $2
# Algoritmo de substituicao de paginas $3
# Intervalo de prints na tela $4
#

all='carrega tests/'$1'.in\nespaco '$2'\nsubstitui '$3'\nexecuta '$4'\nsai'
echo $all | python3 ep3.py

