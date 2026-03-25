# Escaleonamento Em Tempo Real
Implementado em Windows via VS Code Com emulação de WSL via Ubuntu

# Arquivos:

main.c: 

rate.c, rate.h: Onde todos os processos do escaleonamento rate ocorrem

early.c, early.h: Onde todos os processos do escaleonamento early_deadline ocorrem

# Compilação:

Escaleonamento rate-motonic.
    
    make rate 

Escaleonamento earliest-deadline-first.

    make edf

# Execução:
./main 