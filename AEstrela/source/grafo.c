#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

Grafo * inicializar() {
    return NULL;
}

void imprimir(Grafo *g) {
    if (g != NULL) {
        printf("Vertice %d\n", g->id);
        printf("Vizinhos: ");
        Vizinho *v = g->prim_vizinho;
        while(v != NULL) {
            printf("(%d,%d) ", v->id, v->peso);
            v = v->prox;
        }
        printf("\n\n");
        imprimir(g->prox);
    }
}

void liberarGrafo(Grafo *g) {
    if (g != NULL) {
        liberarVizinho(g->prim_vizinho);
        liberarGrafo(g->prox);
        free(g);
    }
}

void liberarVizinho(Vizinho *v) {
    if (v != NULL) {
        liberarVizinho(v->prox);
        free(v);
    }
}

Grafo * buscarVertice(Grafo *g, int id) {
    if (g != NULL && g->id != id) {
        return buscarVertice(g->prox, id);
    }

    return g;
}

Grafo * inserirVertice(Grafo *g, int id) {
    Grafo * p = buscarVertice(g, id);

    if (p == NULL) {
        p = (Grafo*) malloc(sizeof(Grafo));
        p->id = id;
        p->prox = g;
        p->prim_vizinho = NULL;

        g = p;
    }

    return g;
}

Vizinho * buscarAresta(Grafo *g, int v1, int v2) {
    Grafo * pv1 = buscarVertice(g, v1);
    Grafo * pv2 = buscarVertice(g, v2);
    Vizinho * v = NULL;

    if ((pv1 != NULL) && (pv2 != NULL)) {
        v = pv1->prim_vizinho;
        while ((v != NULL) && (v->id != v2)) {
            v = v->prox;
        }
    }

    return v;
}

Grafo * inserirAresta(Grafo *g, int v1, int v2, int peso) {
    Vizinho * v = buscarAresta(g, v1, v2);

    if (v == NULL) {
        Grafo * p = buscarVertice(g, v1);
        Vizinho * novaAresta = (Vizinho *) malloc(sizeof(Vizinho));
        novaAresta->id = v2;
        novaAresta->peso = peso;
        novaAresta->prox = p->prim_vizinho;
        p->prim_vizinho = novaAresta;
    }

    return g;
}

Grafo * clonar(Grafo *g) {
    static Grafo * novoGrafo;
    novoGrafo = inicializar();
    novoGrafo = inserirVertice(novoGrafo, g->id);
    
    Vizinho * v_aux = g->prim_vizinho;
    while(v_aux != NULL) {
        inserirAresta(g, novoGrafo->id, v_aux->id, v_aux->peso);
        v_aux = v_aux->prox;
    }

    return novoGrafo;
}
