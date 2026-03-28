# Escalonamento Em Tempo Real
Implementado em Windows via VS Code Com emulação de WSL

# Arquivos:

main.c: Ponto de entrada do programa onde a lógica principal é coordenada.

rate.c / rate.h: Implementacao dos processos do escalonamento rate

early.c / early.h: Implementacao dos processos do escalonamento early_deadline

# Compilação:

Escalonamento para ambas.

    make all

Escalonamento rate-motonic.
    
    make rate 

Escalonamento earliest-deadline-first.

    make edf

# Execução:
./rate

./edf