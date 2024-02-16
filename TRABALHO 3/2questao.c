#include <stdio.h>
#include <stdlib.h>

#define INF 1e9

typedef struct{
    int v;
    double w;
} Aresta;

typedef struct no{
    Aresta aresta;
    struct no *proximo;
} No;

typedef struct{
    No **cabeca;
    int n;
} Grafo;

Grafo *criaGrafo(int n){
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo->cabeca = (No **)malloc(n * sizeof(No *));
    grafo->n = n;
    for (int i = 0; i < n; i++){
        grafo->cabeca[i] = NULL;
    }
    return grafo;
}

void adicionaAresta(Grafo *grafo, int u, int v, double w){
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->aresta.v = v;
    novoNo->aresta.w = w;
    novoNo->proximo = grafo->cabeca[u];
    grafo->cabeca[u] = novoNo;
}

void imprimeCaminhoRecursivamente(int dest, int pred[]){
    if (dest == -1){
        return;
    }
    imprimeCaminhoRecursivamente(pred[dest], pred);
    printf("%d ", dest);
}

void dijkstra(Grafo *grafo, int src, int dest){
    double dist[grafo->n];
    int pred[grafo->n], visitado[grafo->n];

    for (int i = 0; i < grafo->n; i++){
        dist[i] = 0; 
        pred[i] = -1;
        visitado[i] = 0;
    }

    dist[src] = 1; 
    for (int i = 0; i < grafo->n; i++){
        int u = -1;
        for (int j = 0; j < grafo->n; j++)
            if (!visitado[j] && (u == -1 || dist[j] > dist[u]))
                u = j;
        if (dist[u] == 0){ 
            break;
        }
        visitado[u] = 1;

        No *temp = grafo->cabeca[u];
        while (temp){
            int v = temp->aresta.v;
            double w = temp->aresta.w;
            if (!visitado[v] && dist[v] < dist[u] * w){
                dist[v] = dist[u] * w;
                pred[v] = u;
            }
            temp = temp->proximo;
        }
    }

    printf("Caminho mais confiavel de %d para %d:\n", src, dest);
    imprimeCaminhoRecursivamente(dest, pred);
    printf("\n");

    
    printf("Confiabilidade do caminho: %.2f\n", dist[dest]);
}

void liberaMemoria(Grafo *grafo){
    for (int i = 0; i < grafo->n; i++)
    {
        No *no = grafo->cabeca[i];
        while (no)
        {
            No *temp = no;
            no = no->proximo;
            free(temp);
        }
    }
    free(grafo->cabeca);
    free(grafo);
}





int main(){

    int n = 12;
    Grafo *grafo = criaGrafo(n);

    adicionaAresta(grafo, 0, 1, 1.0);
    adicionaAresta(grafo, 0, 2, 0.9);

    adicionaAresta(grafo, 1, 0, 1.0);
    adicionaAresta(grafo, 1, 2, 0.6);
    adicionaAresta(grafo, 1, 3, 0.7);

    adicionaAresta(grafo, 2, 1, 0.6);
    adicionaAresta(grafo, 2, 0, 0.9);
    adicionaAresta(grafo, 2, 4, 0.8);

    adicionaAresta(grafo, 3, 1, 0.7);
    adicionaAresta(grafo, 3, 4, 0.8);
    adicionaAresta(grafo, 3, 6, 0.9);

    adicionaAresta(grafo, 4, 2, 0.8);
    adicionaAresta(grafo, 4, 3, 0.8);
    adicionaAresta(grafo, 4, 5, 0.9);

    adicionaAresta(grafo, 5, 4, 0.9);
    adicionaAresta(grafo, 5, 6, 0.8);
    adicionaAresta(grafo, 5, 8, 0.5);

    adicionaAresta(grafo, 6, 3, 0.9);
    adicionaAresta(grafo, 6, 5, 0.8);
    adicionaAresta(grafo, 6, 7, 0.7);

    adicionaAresta(grafo, 7, 6, 0.7);
    adicionaAresta(grafo, 7, 8, 0.6);
    adicionaAresta(grafo, 7, 9, 0.9);

    adicionaAresta(grafo, 8, 5, 0.5);
    adicionaAresta(grafo, 8, 7, 0.6);
    adicionaAresta(grafo, 8, 9, 1.0);

    adicionaAresta(grafo, 9, 7, 0.9);
    adicionaAresta(grafo, 9, 8, 1.0);

    do
    {
        int Vinicial, Vfinal;
        printf("Informe o vertice inicial: ");
        scanf("%d", &Vinicial);
        printf("Informe o vertice final: ");
        scanf("%d", &Vfinal);
        dijkstra(grafo, Vinicial, Vfinal);
        printf("Deseja continuar? (s/n): ");
        getchar();

    } while (getchar() == 's' || getchar() == 'S');

 

    liberaMemoria(grafo);

    return 0;
}
