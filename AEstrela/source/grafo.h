#ifndef _GRAFO_H
#define _GRAFO_H

typedef struct vizinho {
    int id;
    int peso;
    struct vizinho *prox;
} Vizinho;

typedef struct grafo {
    int id;
    Vizinho *prim_vizinho;
    struct grafo *prox;
} Grafo;

typedef struct grafo_service {
    Grafo *(*inicializar)();
    void (*imprimir)(Grafo *g);
    void (*liberarVizinho)(Vizinho *v);
    void (*liberarGrafo)(Grafo *g);
    Grafo *(*buscarVertice)(Grafo *g, int id);
    Grafo *(*inserirVertice)(Grafo *g, int id);
    Vizinho *(*buscarAresta)(Grafo *g, int v1, int v2);
    Grafo *(*inserirAresta)(Grafo *g, int v1, int v2, int peso);
    Grafo *(*clonar)(Grafo *g);
} GrafoService;

extern const GrafoService grafoService;

#endif
