#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

static Fila *inicializarFila() {
    return NULL;
}

static No *inicializarNo() {
    return NULL;
}

static void imprimirFila(Fila *f) {
    if (f != NULL) {
        printf("Nos: ");
        No * no = f->cabeca;
        while (no != NULL) {
            printf("%d ", no->id);
            no = no->prox;
        }
        printf("\n\n");
    }
}

static Fila *inserirNo(Fila *f, int id) {
    No * novo_no = filaService.inicializarNo();
    novo_no->id = id;
    novo_no->prox = NULL;

    if (f == NULL || f->cabeca == NULL) {
        f->cabeca = novo_no;
        f->cauda = novo_no;
    } else {
        f->cauda->prox = novo_no;
        f->cauda = novo_no;
    }

    return f;
}

static No *retirarNo(Fila *f) {
    if (f == NULL || f->cabeca == NULL) {
        return NULL;
    }

    No * no = f->cabeca;
    f->cabeca = no->prox;
    return no;
}

const FilaService filaService = {
    inicializarFila,
    inicializarNo,
    inserirNo,
    retirarNo
};
