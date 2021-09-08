#ifndef _FILA_H
#define _FILA_H

typedef struct no {
    int id;
    struct no *prox;
} No;

typedef struct fila {
    No *cabeca;
    No *cauda;
} Fila;

typedef struct fila_service {
    Fila *(*inicializarFila)();
    No *(*inicializarNo)();
    Fila *(*inserirNo)(Fila *f, int id);
    No *(*retirarNo)(Fila *f);
} FilaService;

extern const FilaService filaService;

#endif
