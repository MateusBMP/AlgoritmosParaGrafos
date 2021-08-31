#include <stdio.h>
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
            printf("%d ", v->id);
            v = v->prox;
        }
        printf("\n\n");
        imprime(g->prox);
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

void inserirAresta(Grafo *g, int v1, int v2) {
    Vizinho * v = buscarAresta(g, v1, v2);

    if (v == NULL) {
        Grafo * p = buscarVertice(g, v1);
        Vizinho * novaAresta = (Vizinho *) malloc(sizeof(Vizinho));
        novaAresta->id = v2;
        novaAresta->prox = p->prim_vizinho;
        p->prim_vizinho = novaAresta;
    }
}
