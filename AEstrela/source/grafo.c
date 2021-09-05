#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

static Grafo * inicializar() {
    return NULL;
}

static void imprimir(Grafo *g) {
    if (g != NULL) {
        printf("Vertice %d\n", g->id);
        printf("Vizinhos: ");
        Vizinho *v = g->prim_vizinho;
        while(v != NULL) {
            printf("(%d,%d) ", v->id, v->peso);
            v = v->prox;
        }
        printf("\n\n");
        grafoService.imprimir(g->prox);
    }
}

static void liberarGrafo(Grafo *g) {
    if (g != NULL) {
        grafoService.liberarVizinho(g->prim_vizinho);
        grafoService.liberarGrafo(g->prox);
        free(g);
    }
}

static void liberarVizinho(Vizinho *v) {
    if (v != NULL) {
        grafoService.liberarVizinho(v->prox);
        free(v);
    }
}

static Grafo * buscarVertice(Grafo *g, int id) {
    if (g != NULL && g->id != id) {
        return grafoService.buscarVertice(g->prox, id);
    }

    return g;
}

static Grafo * inserirVertice(Grafo *g, int id) {
    Grafo * p = grafoService.buscarVertice(g, id);

    if (p == NULL) {
        p = (Grafo*) malloc(sizeof(Grafo));
        p->id = id;
        p->prox = g;
        p->prim_vizinho = NULL;

        g = p;
    }

    return g;
}

static Vizinho * buscarAresta(Grafo *g, int v1, int v2) {
    Grafo * pv1 = grafoService.buscarVertice(g, v1);
    Grafo * pv2 = grafoService.buscarVertice(g, v2);
    Vizinho * v = NULL;

    if ((pv1 != NULL) && (pv2 != NULL)) {
        v = pv1->prim_vizinho;
        while ((v != NULL) && (v->id != v2)) {
            v = v->prox;
        }
    }

    return v;
}

static Grafo * inserirAresta(Grafo *g, int v1, int v2, int peso) {
    Vizinho * v = grafoService.buscarAresta(g, v1, v2);

    if (v == NULL) {
        Grafo * p = grafoService.buscarVertice(g, v1);
        Vizinho * novaAresta = (Vizinho *) malloc(sizeof(Vizinho));
        novaAresta->id = v2;
        novaAresta->peso = peso;
        novaAresta->prox = p->prim_vizinho;
        p->prim_vizinho = novaAresta;
    }

    return g;
}

static Grafo * clonar(Grafo *g) {
    static Grafo * novoGrafo;
    novoGrafo = grafoService.inicializar();
    novoGrafo = grafoService.inserirVertice(novoGrafo, g->id);
    
    Vizinho * v_aux = g->prim_vizinho;
    while(v_aux != NULL) {
        grafoService.inserirAresta(novoGrafo, novoGrafo->id, v_aux->id, v_aux->peso);
        v_aux = v_aux->prox;
    }

    return novoGrafo;
}

const GrafoService grafoService = {
    inicializar,
    imprimir,
    liberarVizinho,
    liberarGrafo,
    buscarVertice,
    inserirVertice,
    buscarAresta,
    inserirAresta,
    clonar
};
