# Escaleonamento Em Tempo Real
Implementado em Windows via VS Code Com emulação de WSL via Ubuntu

# Arquivos:

main.c: Onde converge todas as funções e o processo inteiro se basea

rate.c, rate.h: Onde todos os processos do escaleonamento rate ocorrem

early.c, early.h: Onde todos os processos do escaleonamento early_deadline ocorrem

# Compilação:

Escaleonamento rate-motonic.
    
    make rate 

Escaleonamento earliest-deadline-first.

    make edf

# Execução:
./rate

./edf