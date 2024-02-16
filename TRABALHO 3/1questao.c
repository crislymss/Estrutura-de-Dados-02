#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define INF 999999
#define TAM 81

typedef struct Vertice{ 
    int discos[4];
}Vertice;

typedef struct Grafo
{
    Vertice *vertices;
    int **arestas;
}Grafo;




Grafo *criargrafo(int n){
    
    Grafo *G;

    G = (Grafo *) malloc(sizeof(Grafo));
    
   
    G->vertices = (Vertice *) malloc(n * sizeof(Vertice));
    
    
    G->arestas = (int **) malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++){
        G->arestas[i] = (int *) calloc(n, sizeof(int));
    }

    return G;
}

void ImprimirMatriz(Grafo *G, int n){
    printf("Vertices: \n"
    "  "
    );
    for(int i = 0; i < n; i++){
        printf(" %d", i);
    }
    printf("\n\n");
    for(int i = 0; i < n; i++){
        printf("%d  ", i);
        for(int j = 0; j < n; j++){
            printf("%d ", G->arestas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void InsereVerticeAresta(Grafo *G) {
    int valores[][8] = {
        {0, 1, 1, 1, 1, 1, 2, 9999},
        {1, 1, 1, 1, 2, 0, 2, 3},
        {2, 1, 1, 1, 3, 0, 1, 4},
        {3, 1, 1, 3, 2, 1, 5, 6},
        {4, 1, 1, 2, 3, 2, 7, 8},
        {5, 1, 1, 3, 3, 3, 6, 9},
        {6, 1, 1, 3, 1, 3, 5, 7},
        {7, 1, 1, 2, 1, 4, 6, 8},
        {8, 1, 1, 2, 2, 4, 7, 10},
        {9, 1, 2, 3, 3, 5, 11, 12},
        {10, 1, 3, 2, 2, 8, 13, 14},
        {11, 1, 2, 3, 1, 9, 12, 15},
        {12, 1, 2, 3, 2, 9, 11, 16},
        {13, 1, 3, 2, 3, 10, 14, 17},
        {14, 1, 3, 2, 1, 10, 13, 18},
        {15, 1, 2, 2, 1, 11, 16, 19},
        {16, 1, 2, 1, 2, 12, 21, 22},
        {17, 1, 3, 1, 3, 13, 23, 24},
        {18, 1, 3, 3, 1, 14, 25, 26},
        {19, 1, 2, 2, 2, 15, 20, 27},
        {20, 1, 2, 2, 3, 15, 19, 21},
        {21, 1, 2, 1, 3, 16, 20, 22},
        {22, 1, 2, 1, 1, 16, 21, 23},
        {23, 1, 3, 1, 1, 17, 22, 24},
        {24, 1, 3, 1, 2, 17, 23, 25},
        {25, 1, 3, 3, 2, 18, 24, 26},
        {26, 1, 3, 3, 3, 18, 25, 28},
        {27, 3, 2, 2, 2, 19, 29, 30},
        {28, 2, 3, 3, 3, 26, 31, 32},
        {29, 3, 2, 2, 3, 27, 30, 33},
        {30, 3, 2, 2, 1, 27, 29, 34},
        {31, 2, 3, 3, 1, 28, 31, 32},
        {32, 2, 3, 3, 2, 28, 31, 36},
        {33, 3, 2, 1, 3, 29, 37, 38},
        {34, 3, 2, 3, 1, 30, 39, 40},
        {35, 2, 3, 2, 1, 31, 41, 42},
        {36, 2, 3, 1, 2, 32, 43, 44},
        {37, 3, 2, 1, 1, 33, 38, 45},
        {38, 3, 2, 1, 2, 33, 37, 39},
        {39, 3, 2, 3, 2, 34, 38, 40},
        {40, 3, 2, 3, 3, 34, 39, 46},
        {41, 2, 3, 2, 2, 35, 42, 47},
        {42, 2, 3, 2, 3, 35, 41, 43},
        {43, 2, 3, 1, 3, 36, 42, 44},
        {44, 2, 3, 1, 1, 36, 43, 48},
        {45, 3, 3, 1, 1, 37, 49, 50},
        {46, 3, 1, 3, 3, 40, 51, 52},
        {47, 2, 1, 2, 2, 41, 53, 54},
        {48, 2, 2, 1, 1, 44, 55, 56},
        {49, 3, 3, 1, 2, 45, 50, 57},
        {50, 3, 3, 1, 3, 45, 49, 58},
        {51, 3, 1, 3, 1, 46, 52, 59},
        {52, 3, 1, 3, 2, 46, 51, 60},
        {53, 2, 1, 2, 3, 47, 54, 61},
        {54, 2, 1, 2, 1, 47, 53, 62},
        {55, 2, 2, 1, 2, 48, 56, 63},
        {56, 2, 2, 1, 3, 48, 55, 64},
        {57, 3, 3, 3, 2, 49, 65, 66},
        {58, 3, 3, 2, 3, 50, 67, 68},
        {59, 3, 1, 2, 1, 51, 69, 70},
        {60, 3, 1, 1, 2, 52, 71, 72},
        {61, 2, 1, 1, 3, 53, 73, 74},
        {62, 2, 1, 3, 1, 54, 75, 76},
        {63, 2, 2, 3, 2, 55, 77, 78},
        {64, 2, 2, 2, 3, 56, 79, 80},
        {65, 3, 3, 3, 3, 57, 66, 9999},
        {66, 3, 3, 3, 1, 57, 65, 67},
        {67, 3, 3, 2, 1, 58, 66, 68},
        {68, 3, 3, 2, 2, 58, 67, 69},
        {69, 3, 1, 2, 2, 59, 68, 70},
        {70, 3, 1, 2, 3, 59, 69, 71},
        {71, 3, 1, 1, 3, 60, 70, 72},
        {72, 3, 1, 1, 1, 60, 71, 73},
        {73, 2, 1, 1, 1, 61, 72, 74},
        {74, 2, 1, 1, 2, 61, 73, 75},
        {75, 2, 1, 3, 2, 62, 74, 76},
        {76, 2, 1, 3, 3, 62, 75, 77},
        {77, 2, 2, 3, 3, 63, 76, 78},
        {78, 2, 2, 3, 1, 63, 77, 79},
        {79, 2, 2, 2, 1, 64, 78, 80},
        {80, 2, 2, 2, 2, 64, 79, 9999}
    };

    int tamanhoValores = 81;

    int i = 0;
    while (i < tamanhoValores) {
        int verticeAtual = valores[i][0];
        int disco1 = valores[i][1];
        int disco2 = valores[i][2];
        int disco3 = valores[i][3];
        int disco4 = valores[i][4];
        int aresta1 = valores[i][5];
        int aresta2 = valores[i][6];
        int aresta3 = valores[i][7];

        G->vertices[verticeAtual].discos[0] = disco1;
        G->vertices[verticeAtual].discos[1] = disco2;
        G->vertices[verticeAtual].discos[2] = disco3;
        G->vertices[verticeAtual].discos[3] = disco4;

        G->arestas[verticeAtual][aresta1] = 1;
        G->arestas[verticeAtual][aresta2] = 1;
        if (aresta3 != 9999)
            G->arestas[verticeAtual][aresta3] = 1;

        i++;
    }

}


void ImprimirVertice(Grafo *G, int linha){
    printf("%d: (%d, %d, %d, %d)\n", linha, G->vertices[linha].discos[0], G->vertices[linha].discos[1], G->vertices[linha].discos[2], G->vertices[linha].discos[3]);
}

void Menorcaminho_DijsktranBelman(int vertices, int destino, int vertice_anterior[], int distancia[]){
   
    printf("\nCaminho mais curto: ");
    int comprimentocaminho = 0;
    int *caminhovertices; caminhovertices = (int*)malloc(vertices * sizeof(int));

    int verticeatual = destino;

    while (verticeatual != -1) {
        caminhovertices[comprimentocaminho++] = verticeatual;
        verticeatual = vertice_anterior[verticeatual];
    }

    for (int i = comprimentocaminho - 1; i >= 0; i--) {
        printf("%d ", caminhovertices[i]);
        if (i > 0)
            printf(" - ");
    }
    printf("\nDistancia: %d\n", distancia[destino]);
    free(caminhovertices);
}

void bellmanFord(int **grafo, int vertices, int origem, int destino) {
    int temciclonegativo = 0;
    int *distancia, *vertice_anterior;
    distancia = (int*)malloc(vertices * sizeof(int));
    vertice_anterior = (int*)malloc(vertices * sizeof(int));
 
    for (int i = 0; i < vertices; i++) {
        distancia[i] = INF;
        vertice_anterior[i] = -1;
    }

    distancia[origem] = 0;

    for (int qtdRelaxamentos = 0; qtdRelaxamentos < vertices - 1; qtdRelaxamentos++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (grafo[i][j] && distancia[i] != INF && distancia[i] + grafo[i][j] < distancia[j]) {
                    distancia[j] = distancia[i] + grafo[i][j];
                    vertice_anterior[j] = i;
                }
            }
        }
    }


    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (grafo[i][j] && distancia[i] != INF && distancia[i] + grafo[i][j] < distancia[j]) {
                printf("O grafo contem um ciclo negativo.\n");
                temciclonegativo = 1;
                j = vertices;
                i = j;
            }
        }
    }
 
    if(!temciclonegativo)
        Menorcaminho_DijsktranBelman(vertices,destino,vertice_anterior,distancia);
    free(distancia);
    free(vertice_anterior);
}

void liberarMemoria(Grafo **G, int qtdVertice){
    for (int i = 0; i < qtdVertice; i++){
        free((*G)->arestas[i]);
        (*G)->arestas[i] = NULL;
    }
    free((*G)->vertices);
    (*G)->vertices = NULL;

    free(*G);
    *G = NULL;
}


void lugarDasArestas(int *vetorVertice, int *resposta, int *cont){
    *cont = 0;

    for(int i = 0; i < 81; i++){
        if(vetorVertice[i] == 1){
            if(*cont == 0)
                resposta[0] = i;
            if(*cont == 1)
                resposta[1] = i;
            if(*cont == 2)
                resposta[2] = i;
            *cont += 1;
        }
    }
}


int verificarOpcaoPraOndeIr(int *resposta, int vertice){
    int cont = 1;
    if (vertice == resposta[0]) 
        cont = 0;
    if (vertice == resposta[1])
        cont = 0;
    if (vertice == resposta[2])
        cont = 0;
    
    return cont;
}




int main()
{
    Grafo *G;
    int op = 0, vertice, cont, resposta[3], origem, destino;
    

    G = criargrafo(81);

    InsereVerticeAresta(G);

    while (op != 6)
    {
        printf("1 - Imprimir Valores de Todos os Vertices\n");
        printf("2 - Imprimir um Vertice\n");
        printf("3 - Imprimir Matriz de Adjacencia\n");
        printf("4 - Imprimir Para Onde as Arestas de Vertice Estao Ligadas\n");
        printf("5 - Menor Caminho Utilizando Ford-Moore-Bellman\n");
        printf("6 - Sair\n");
        printf("Informe uma opcao:\n");
        scanf("%d", &op);

        switch (op)
        {
      
            case 1:{
                for (int i = 0; i < TAM; i++)
                    ImprimirVertice(G, i); 
                break;
            }
            case 2:{
                printf("Digite o indice do vertice: ");
                scanf("%d", &vertice);
                if (vertice >= 0 && vertice <= 80)
                    ImprimirVertice(G, vertice);
                else
                    printf("Indice de vertice não existe.\n");
                break;
            }
            case 3:{
                ImprimirMatriz(G, TAM); 
                break;
            }
            case 4:{
                cont = 0;
                printf("Digite o indice do vertice: ");
                scanf("%d", &vertice);

                if (vertice >= 0 && vertice <= 80){
                    lugarDasArestas(G->arestas[vertice], resposta, &cont);

                    ImprimirVertice(G, resposta[0]);
                    ImprimirVertice(G, resposta[1]);

                    if (cont == 3)
                    {
                        ImprimirVertice(G, resposta[2]);
                    }
                    memset(resposta, 0, sizeof(resposta));
                }
                else
                    printf("Indice de vertice não existe.\n");
                break;
            }
            
            case 5:{
                double elapsed_nanos;
                LARGE_INTEGER start, end, frequency;
            
        
                printf("Ford-Moore-Bellman\n");
                printf("Digite o vertice de origem: ");
                scanf("%d", &origem);
                printf("Digite o vertice de destino: ");
                scanf("%d", &destino);

                if ((origem >= 0 && origem <= 80) && (destino >= 0 && destino <= 80)){
                    QueryPerformanceFrequency(&frequency);
                    QueryPerformanceCounter(&start);
                    bellmanFord(G->arestas, TAM, origem, destino);
                    QueryPerformanceCounter(&end);

                    elapsed_nanos = ((end.QuadPart - start.QuadPart) * 1.0 / frequency.QuadPart) * 1000000000;
                    printf("Tempo de execucao: %.2f nanossegundos\n", elapsed_nanos);
                }
                else{
                    printf("Verifique se os vertices informados existem\n");
                }
                break;
            }
            
            case 6:{
                break;
            }
        
            default:
                printf("Opcao Invalida\n");
                break;
        }
    }
    liberarMemoria(&G, 81);
    return 0;
}