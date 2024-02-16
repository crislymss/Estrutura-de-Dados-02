#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//erikfazendoteste
//cris fazendo teste


#define Black 0
#define Red 1


typedef struct Musica{
    char tituloMusica[200];
    float minutos;
    struct Musica *Prox;
}Musica;


typedef struct Albuns{
    char tituloAlbum[200];
    int ano;
    int quantmusica;
    int cor;
    struct Musica *musica;
    struct Albuns *Esq;
    struct Albuns *Dir;


}Albuns;

typedef struct Artista{
    char artista[200];
    char TipoArtista[200];
    char estilomusical[100];
    int numAlbuns;
    int Cor;
    struct Albuns *albuns;
    struct Artista *Esq;
    struct Artista *Dir;
  
}Artista;







int CadastraMusica(Musica **lista, char *TituloMusica, float min){
    int sabe = 1;
 
    Musica *aux = *lista;
    while (aux != NULL && sabe != 0) {
        if (strcmp(TituloMusica, aux->tituloMusica) == 0) {
            sabe = 0; 
    
        }
        aux = aux->Prox;
    }

    if(sabe != 0){

        Musica *novaMusica = (Musica*)malloc(sizeof(Musica));
    
        strcpy(novaMusica->tituloMusica, TituloMusica);
        novaMusica->minutos = min;
        
        novaMusica->Prox = NULL;  

        if (*lista == NULL) {
            *lista = novaMusica;
        } 
        else {
            Musica *aux = *lista;
            Musica *ant = NULL;
            
            while (aux != NULL && strcmp(novaMusica->tituloMusica, aux->tituloMusica) > 0) {
                ant = aux;
                aux = aux->Prox;
            }

            if (ant == NULL) {
                novaMusica->Prox = *lista;
                *lista = novaMusica;
            }
            else {
                ant->Prox = novaMusica;
                novaMusica->Prox = aux;
            }
        }

    }

    return sabe;
}


Albuns *rotacionaDireitaAlbuns(Albuns *raiz)
{
    Albuns *Aux = raiz->Esq;
    raiz->Esq = Aux->Dir;
    Aux->Dir = raiz;
    Aux->cor = raiz->cor;
    raiz->cor = Red;

    return Aux;
}

Albuns *rotacionaEsquerdaAlbuns(Albuns *raiz)
{
    Albuns *Aux = raiz->Dir;
    raiz->Dir = Aux->Esq;
    Aux->Esq = raiz;
    Aux->cor = raiz->cor;
    raiz->cor = Red;

    return Aux;

}

void trocaCorAlbuns(Albuns *raiz)
{
    raiz->cor = !raiz->cor;

    if (raiz->Esq != NULL)
    {
        raiz->Esq->cor = !raiz->Esq->cor;
    }

    if (raiz->Dir != NULL)
    {
        raiz->Dir->cor = !raiz->Dir->cor;
    }
}

Artista *rotacionaDireita(Artista *raiz){
    Artista *Aux = (raiz)->Esq;
    (raiz)->Esq = Aux->Dir;
    Aux->Dir = raiz;
    Aux->Cor = (raiz)->Cor;
    (raiz)->Cor = Red;

    return Aux;

}

Artista  *rotacionaEsquerda(Artista *raiz) {
    Artista *aux = (raiz)->Dir;
    (raiz)->Dir = aux->Esq;
    aux->Esq = raiz;
    aux->Cor = (raiz)->Cor;
    (raiz)->Cor = Red;

    return aux;
}


void trocaCor(Artista *raiz){
    (raiz)->Cor = !(raiz)->Cor;

    if((raiz)->Esq != NULL){
        (raiz)->Esq->Cor = !(raiz)->Esq->Cor;
    }

    if((raiz)->Dir != NULL){
        (raiz)->Dir->Cor = !(raiz)->Dir->Cor; 
    }
}


Artista* Balancear(Artista *raiz) {
    //No vermelho é sempre filho à esquerda
    if (raiz->Dir != NULL && raiz->Dir->Cor == Red) {
        raiz = rotacionaEsquerda(raiz);
    }

    //Filho da direita e neto da esquerda são vermelhos
    if (raiz->Esq != NULL && raiz->Esq->Cor == Red && raiz->Esq->Esq->Cor == Red) {
        raiz = rotacionaDireita(raiz);
    }

    //Dois filhos vermelhos: trocar cor!!!
    if (raiz->Esq->Cor == Red && raiz->Dir->Cor == Red) {
        trocaCor(raiz);
    }

    return raiz;
}

Albuns* Balancear_album(Albuns *raiz) {
    //No vermelho é sempre filho à esquerda
    if (raiz->Dir != NULL && raiz->Dir->cor == Red) {
        raiz = rotacionaEsquerdaAlbuns(raiz);
    }

    //Filho da direita e neto da esquerda são vermelhos
    else if (raiz->Esq != NULL && raiz->Esq->Esq != NULL && raiz->Dir != NULL && raiz->Dir->cor == Red && raiz->Esq->Esq->cor == Red) {
        raiz = rotacionaDireitaAlbuns(raiz);
    }

    //Dois filhos vermelhos: trocar cor!!!
    else if (raiz->Esq != NULL && raiz->Dir != NULL && raiz->Esq->cor == Red && raiz->Dir->cor == Red) {
        trocaCorAlbuns(raiz);
    }

    return raiz;
}




Artista* move2EsqRED(Artista *raiz) {
    trocaCor(raiz);
    if (raiz->Dir->Esq->Cor == Red) {
        raiz->Dir = rotacionaDireita(raiz->Dir);
        raiz = rotacionaEsquerda(raiz);
        trocaCor(raiz);
    }

    return raiz;
}



Artista* move2DirRED(Artista *raiz) {
    trocaCor(raiz);
    if (raiz->Esq->Esq->Cor == Red) {
        raiz = rotacionaDireita(raiz);
        trocaCor(raiz);
    }

    return raiz;
}


Albuns* move2EsqRED_album(Albuns *raiz) {
    trocaCorAlbuns(raiz);
    if (raiz->Dir->Esq != NULL && raiz->Dir->Esq->cor == Red) {
        raiz->Dir = rotacionaDireitaAlbuns((raiz->Dir));
        raiz = rotacionaEsquerdaAlbuns(raiz);
        trocaCorAlbuns(raiz);
    }

    return raiz;
}

Albuns* move2DirRED_album(Albuns *raiz) {
    trocaCorAlbuns(raiz);
    if (raiz->Dir->Esq->cor == Red) {
        raiz->Dir = rotacionaDireitaAlbuns((raiz->Dir));
        raiz = rotacionaEsquerdaAlbuns(raiz);
        trocaCorAlbuns(raiz);
    }

    return raiz;
}

Artista* removeMenor(Artista *raiz) {
    if (raiz != NULL) {
        if (raiz->Esq->Cor == Black && (raiz->Esq->Esq->Cor == Black)) {
            raiz = move2EsqRED(raiz);
        }
        raiz->Esq = removeMenor(raiz->Esq);
        raiz = Balancear(raiz);
    } else {
        free(raiz);
        raiz = NULL;
    }
    return raiz;
}


Albuns* removeMenor_album(Albuns *raiz) {
    if (raiz != NULL) {
        if (raiz->Esq != NULL) {
            if (raiz->Esq->cor == Black && (raiz->Esq->Esq == NULL || raiz->Esq->Esq->cor == Black)) {
                raiz = move2EsqRED_album(raiz);
            }
            raiz->Esq = removeMenor_album(raiz->Esq);
        } else {
            free(raiz);
            raiz = NULL;
        }

        if (raiz != NULL) {
            raiz = Balancear_album(raiz);
        }
    }
    return raiz;
}



Artista* procuraMenor(Artista *raizAtual){
    Artista *no1 = raizAtual;
    Artista *no2 = raizAtual->Esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->Esq;
    }

    return no1;
}

Albuns* procuraMenor_album(Albuns *raizAtual){
    Albuns *no1 = raizAtual;
    Albuns *no2 = raizAtual->Esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->Esq;
    }

    return no1;
}

int ArtistaExiste(Artista *raiz, char *nomeArtista)
{
    return (raiz != NULL) && 
           ((strcmp(raiz->artista, nomeArtista) == 0) || 
           ArtistaExiste(raiz->Esq, nomeArtista) || 
           ArtistaExiste(raiz->Dir, nomeArtista));
}


Artista *InsereNoArtista(Artista *raiz, char *novoArtista, int *resp)
{ 
    
    if (ArtistaExiste(raiz, novoArtista))
    {
        *resp = 0;
    }

    else if (raiz == NULL)
    {
        Artista *novo = (Artista *)malloc(sizeof(Artista));
        if (novo == NULL)
        {
            *resp = 0;
        }
        else
        {
            strcpy(novo->artista, novoArtista);

            printf("Informe o Estilo Musical:\n");
            fflush(stdin);
            scanf("%[^\n]", novo->estilomusical);

            printf("Informe o Tipo do Artista:\n");
            fflush(stdin);
            scanf("%[^\n]", novo->TipoArtista);

            novo->albuns = NULL;
            novo->Cor = Red;
            novo->Dir = NULL;
            novo->Esq = NULL;
            novo->numAlbuns = 0;
            *resp = 1;
            raiz = novo; 
        }
    }
    else
    {
        if (strcmp(novoArtista, raiz->artista) < 0)
        {
            raiz->Esq = InsereNoArtista(raiz->Esq, novoArtista, resp);
        }
        else
        {
            raiz->Dir = InsereNoArtista(raiz->Dir, novoArtista, resp);
        }

        if (raiz->Dir != NULL && raiz->Dir->Cor == Red && (raiz->Esq == NULL || raiz->Esq->Cor == Black))
        {
          raiz = rotacionaEsquerda(raiz);  
        }

        if (raiz->Esq != NULL && raiz->Esq->Cor == Red && raiz->Esq->Esq != NULL && raiz->Esq->Esq->Cor == Red)
        {
            raiz = rotacionaDireita(raiz);
        }

        if (raiz->Esq != NULL && raiz->Esq->Cor == Red && raiz->Dir != NULL && raiz->Dir->Cor == Red)
        {
            trocaCor(raiz);
        }
    }

    return raiz;
}


int InsereArvRBArtista(Artista **raiz, char *nomeArtista) {
    int resp;
    *raiz = InsereNoArtista(*raiz, nomeArtista, &resp);

    if (*raiz != NULL) {
        (*raiz)->Cor = Black;
    }

    return resp;
}

Albuns *InsereArvRBAlbuns(Albuns *raiz, Artista *artista, char *novoAlbum, int *resp)
{
    Albuns *retorno = raiz; 

  
    if (artista != NULL)
    {
 
        if (raiz == NULL)
        {
            Albuns *novo = (Albuns *)malloc(sizeof(Albuns));
            if (novo != NULL)
            {
                strcpy(novo->tituloAlbum, novoAlbum);
                printf("Informe o Ano do Album:\n");
                scanf("%d", &novo->ano);
                printf("Informe a Quantidade de Musicas:\n");
                scanf("%d", &novo->quantmusica);
                novo->musica = NULL;
                novo->cor = Red;
                novo->Dir = NULL;
                novo->Esq = NULL;
              
                *resp = 1;

                artista->numAlbuns++;

                retorno = novo; 
            }
            else
            {
                *resp = 0;
            }
        }
        else
        {
            int comp = strcmp(novoAlbum, raiz->tituloAlbum);
            if (comp != 0)
            {
               
                if (strcmp(novoAlbum, raiz->tituloAlbum) < 0)
                {
                    raiz->Esq = InsereArvRBAlbuns(raiz->Esq, artista, novoAlbum, resp);
                }
                else
                {
                    raiz->Dir = InsereArvRBAlbuns(raiz->Dir, artista, novoAlbum, resp);
                }

              
                if (raiz->Dir != NULL && raiz->Dir->cor == Red && (raiz->Esq == NULL || raiz->Esq->cor == Black))
                {
                    raiz = rotacionaEsquerdaAlbuns(raiz);
                }

                if (raiz->Esq != NULL && raiz->Esq->cor == Red && raiz->Esq->Esq != NULL && raiz->Esq->Esq->cor == Red)
                {
                    raiz = rotacionaDireitaAlbuns(raiz);
                }

                if (raiz->Esq != NULL && raiz->Esq->cor == Red && raiz->Dir != NULL && raiz->Dir->cor == Red)
                {
                    trocaCorAlbuns(raiz);
                }
            }
            else
            {
                *resp = 0;
            }
        }
    }
    else
    {
        *resp = 0;
    }

    return retorno; 
}

int InsereArvNoAlbum(Albuns **raiz, Artista *artista, char *nomeAlbum)
{
    int resp;
    *raiz = InsereArvRBAlbuns(*raiz, artista, nomeAlbum, &resp);

    if (*raiz != NULL)
    {
        (*raiz)->cor = Black;
    }

    return resp;
}


Artista *remove_NO(Artista *raiz, char *nomeArtista){
    printf("ENTROU MESMOOOO\n");
    if(strcmp(nomeArtista, raiz->artista) < 0){
        printf("ENTROU QUANDO O VALOR E MENOR\n");
        if((raiz->Esq->Cor == Black) && (raiz->Esq->Esq->Cor == Black)){
            raiz = move2EsqRED(raiz);
        }

        raiz->Esq = remove_NO(raiz->Esq, nomeArtista);
    }
    else{
        printf("Entrou no ELSE\n");
        if(raiz->Esq->Cor == Red){
            printf("ENTROU NO IF DA ROTACAO QUANDO E VERMELHO");
            raiz = rotacionaDireita(raiz);
        }

        if((strcmp(nomeArtista, raiz->artista) == 0) && (raiz->Dir == NULL)){
            printf("ENTROU QUANDO A DIR E NULL E E O VALOR QUE QUEREMOS REMOVER\n");
            free(raiz);
            return NULL;
        }

        printf("ESTAMOS EM CIMA DA ONDE E PRA ENTRAR\n");
        printf("COR DA DIR DA RAIZ: %d\n", raiz->Dir->Cor);
        if((raiz->Dir->Cor == Black) && ((raiz->Dir->Esq->Cor == Black) || (raiz->Dir->Esq == NULL))){
            printf("ENTROU NO MOVE2DIRRED!!\n");
            raiz = move2DirRED(raiz);
        }
        printf("Passou da condicao que e pra entrar\n");
        if(strcmp(nomeArtista, raiz->artista) == 0){
            printf("ENTROU QUANDO E SO IGUAL\n");
            Artista *Aux = procuraMenor(raiz->Dir);
            strcpy(raiz->artista, Aux->artista);
            raiz->Dir = removeMenor(raiz->Dir);
        }else{
            raiz->Dir = remove_NO(raiz->Dir, nomeArtista);
        }

        
    }

    return Balancear(raiz);
}

Albuns *remove_NO_album(Albuns *raiz, char *nomeAlbum){
    if (raiz == NULL) {
        return NULL;
    }

    if (strcmp(nomeAlbum, raiz->tituloAlbum) < 0){
        if (raiz->Esq != NULL) {
            if (raiz->Esq->cor == Black && (raiz->Esq->Esq == NULL || raiz->Esq->Esq->cor == Black)) {
                raiz = move2EsqRED_album(raiz);
            }
            raiz->Esq = remove_NO_album(raiz->Esq, nomeAlbum);
        }
    }
    
    else if (strcmp(nomeAlbum, raiz->tituloAlbum) > 0){
        if (raiz->Dir != NULL) {
            if (raiz->Esq->cor == Red) {
                raiz = remove_NO_album(raiz->Dir, nomeAlbum);
            }

            if (strcmp(nomeAlbum, raiz->tituloAlbum) == 0 && (raiz->Dir == NULL)) {
                free(raiz);
                return NULL;
            }

            if (raiz->Dir != NULL && raiz->Dir->cor == Black && (raiz->Dir->Esq == NULL || raiz->Dir->Esq->cor == Black)) {
                raiz = move2DirRED_album(raiz);
            }

            if (strcmp(nomeAlbum, raiz->tituloAlbum) == 0) {
                Albuns *x = procuraMenor_album(raiz->Dir);
                strcpy(raiz->tituloAlbum, x->tituloAlbum);
                raiz->Dir = removeMenor_album(raiz->Dir);
            }
            else {
                raiz->Dir = remove_NO_album(raiz->Dir, nomeAlbum);
            }
        }
    }

    raiz = Balancear_album(raiz);
    return raiz;
}


int remove_Artista(Artista **raiz, char *nomeArtista){
   int sabe;
   int resultado = 0;
   sabe = ArtistaExiste(*raiz, nomeArtista);
   if(sabe == 1){
    printf("Artista encontrado!\n");
    Artista *Aux = *raiz;
    printf("Entrando em remove no\n");
    *raiz = remove_NO(Aux, nomeArtista);
    printf("saiu de remove no\n");
    if(*raiz != NULL){
        (*raiz)->Cor = Black;
        resultado = 1;
    }
   }
   return resultado;
}


int remove_Album(Albuns **raiz, char *nomeAlbum){
    int resultado = 0;  // Não encontrou o album para remover
    if (*raiz != NULL) {
        *raiz = remove_NO_album(*raiz, nomeAlbum);
        if (*raiz != NULL) {
            (*raiz)->cor = Black;
            resultado = 1;  // Remoção bem-sucedida
        }
    }
    return resultado;
}


Artista *excluir_artista(Artista *raiz, char *nome) 
{
    if (raiz == NULL) {
        return NULL;
    }

    if (strcmp(nome, raiz->artista) < 0) 
        raiz->Esq = excluir_artista(raiz->Esq, nome);
    else if (strcmp(nome, raiz->artista) > 0) 
        raiz->Dir = excluir_artista(raiz->Dir, nome);
    else 
    {

        if (raiz->Esq == NULL && raiz->Dir == NULL)
        { //sem filho
            
            free(raiz);
            return NULL;
        } 
        else if (raiz->Esq == NULL || raiz->Dir == NULL) 
        { //um filho
            
            Artista *temp = (raiz->Esq != NULL) ? raiz->Esq : raiz->Dir;
            free(raiz);
            return temp;
        } 
        else 
        { //dois filhos
            Artista *temp = procuraMenor(raiz->Dir);
            raiz = temp;
            raiz->Dir = excluir_artista(raiz->Dir, temp->artista);
        }


    }

    Balancear(raiz);

    return raiz;
}

Albuns *excluir_Album(Albuns *raiz, char *nome) 
{
    if (raiz == NULL) {
        return NULL;
    }

    if (strcmp(nome, raiz->tituloAlbum) < 0) 
        raiz->Esq = excluir_Album(raiz->Esq, nome);
    else if (strcmp(nome, raiz->tituloAlbum) > 0) 
        raiz->Dir = excluir_Album(raiz->Dir, nome);
    else 
    {

        if (raiz->Esq == NULL && raiz->Dir == NULL)
        { //sem filho
            
            free(raiz);
            return NULL;
        } 
        else if (raiz->Esq == NULL || raiz->Dir == NULL) 
        { //um filho
            
            Albuns *temp = (raiz->Esq != NULL) ? raiz->Esq : raiz->Dir;
            free(raiz);
            return temp;
        } 
        else 
        { //dois filhos
            Albuns *temp = procuraMenor_album(raiz->Dir);
            raiz = temp;
            raiz->Dir = excluir_Album(raiz->Dir, temp->tituloAlbum);
        }

    }

    Balancear_album(raiz);

    return raiz;
}

void  remover_musica(Musica **lista, char *TituloMusica){
    Musica *aux = *lista;
    Musica *ant = NULL;

  
    while (aux != NULL && strcmp(TituloMusica, aux->tituloMusica) != 0) {
        ant = aux;
        aux = aux->Prox;
    }

    if (aux != NULL) {
    
        if (ant == NULL) {
            *lista = aux->Prox;
        }
       
        else {
            ant->Prox = aux->Prox;
        }

        printf("Música '%s' removida com sucesso.\n", TituloMusica);

        free(aux);
    } else {
        printf("Música '%s' não encontrada.\n", TituloMusica);
    }


}





void imprime(Artista *raiz)
{

    if(raiz != NULL){
        imprime(raiz->Esq);
        printf("Nome do Artista: %s\n", raiz->artista);
        printf("Estilo Musical: %s\n", raiz->estilomusical);
        printf("Tipo do Artista: %s\n", raiz->TipoArtista);
        printf("Numero de Albuns: %d\n", raiz->numAlbuns);
        imprime(raiz->Dir);
    }
}

void mostrarDadosArtista(Artista *raiz, char *nomeArtista){
    if(raiz != NULL){
        if(strcmp(raiz->artista, nomeArtista) == 0){
            printf("Nome do Artista: %s\n", raiz->artista);
            printf("Estilo Musical: %s\n", raiz->estilomusical);
            printf("Quantidade de Albuns: %d\n", raiz->numAlbuns);
        }
        mostrarDadosArtista(raiz->Esq, nomeArtista);
        mostrarDadosArtista(raiz->Dir, nomeArtista);
    }
}

Artista *BuscarArtista(Artista **raiz, char *nomeArtista){
    Artista *result = NULL;
    if (*raiz!=NULL){
        if (strcmp(nomeArtista, (*raiz)->artista) == 0){
            result = *raiz;
        }
        else{
            if (strcmp(nomeArtista, (*raiz)->artista) < 0){
                result = BuscarArtista(&(*raiz)->Esq, nomeArtista);
            }
            else{
                result = BuscarArtista(&(*raiz)->Dir, nomeArtista);
            }
        }
    }

    return result;
}


Albuns *BuscarAlbum(Albuns **raiz, char *nomealbum){
    Albuns *result = NULL;
    if (*raiz!=NULL){
        if (strcmp(nomealbum, (*raiz)->tituloAlbum) == 0){
            result = *raiz;
        }
        else{
            if (strcmp(nomealbum, (*raiz)->tituloAlbum) < 0){
                result = BuscarAlbum(&(*raiz)->Esq, nomealbum);
            }
            else{
                result = BuscarAlbum(&(*raiz)->Dir, nomealbum);
            }
        }
    }

    return result;
}


Musica* BuscaMusica(Musica *lista, char *TituloMusica) {
    Musica *aux = lista;
    
    // Percorra a lista
    while (aux != NULL) {
        // Se o título da música atual corresponder ao título da música procurada
        if (strcmp(TituloMusica, aux->tituloMusica) == 0) {
            return aux; // Retorne a música
        }
        aux = aux->Prox;
    }
    
    // Se a música não foi encontrada na lista
    return NULL;
}

void imprimeAlbuns(Albuns *raiz)
{
    if (raiz != NULL)
    {
        imprimeAlbuns(raiz->Esq);
        printf("Nome do Album: %s\n", raiz->tituloAlbum);
        printf("Ano: %d\n", raiz->ano);
        printf("Quantidade de Musicas: %d\n", raiz->quantmusica);
        printf("\n");
        imprimeAlbuns(raiz->Dir);
    }
}

void imprimeMusica(Musica *lista)
{
    Musica *aux = lista;


    while (aux != NULL)
    {
        printf("Titulo da Musica: %s\n", aux->tituloMusica);
        printf("Duracao: %.2f\n", aux->minutos);
        printf("\n");
        aux = aux->Prox;
    }
}



void liberaMusica(Musica **lista){
    if(*lista != NULL){
        liberaMusica(&((*lista)->Prox));
        free(*lista);
        *lista = NULL;
    }
}

void liberaAlbum(Albuns **raiz){
    if(*raiz != NULL){
        liberaAlbum(&((*raiz)->Esq));
        liberaAlbum(&((*raiz)->Dir));
        liberaMusica(&((*raiz)->musica));
        free(*raiz);
        *raiz = NULL;
    }
}

void liberaArtista(Artista **raiz){
    if(*raiz != NULL){
        liberaArtista(&((*raiz)->Esq));
        liberaArtista(&((*raiz)->Dir));
        liberaAlbum(&((*raiz)->albuns));
        liberaMusica(&((*raiz)->albuns->musica));
        free(*raiz);
        *raiz = NULL;
    }
}


int main(){
    Artista *RaizArtista;
    RaizArtista = NULL;
    char nomeArtista[200];
    char nomeAlbum[200];
    int op;
    while(1){

        printf("==========MENU==========\n");
        printf("1- Cadastrar Artista\n");
        printf("2- Cadastrar Album\n");
        printf("3- Cadastrar Musica\n");
        printf("4- Buscar\n");
        printf("5- Remover\n");
        printf("6- Imprimir\n");
        printf("7- Sair\n");
        scanf("%d", &op);

    
        switch (op)
        {
        case 1:{
            
            
            int recebeu;
            printf("Informe o Nome do Artista:\n");
            fflush(stdin);
            scanf("%[^\n]", nomeArtista);
        
            recebeu = InsereArvRBArtista(&RaizArtista, nomeArtista);

            

            if(recebeu == 1){
                printf("Artista Cadastrado Com Sucesso!\n");
            }
            else{
                printf("Artista informado ja esta cadastrado!\n");
            }
            break;

        }
        case 2:{

            int recebeu;
            printf("Informe o Nome do Artista:\n");
            fflush(stdin);
            scanf("%[^\n]", nomeArtista);

            Artista *verifica;
            verifica = BuscarArtista(&RaizArtista, nomeArtista);

            if(verifica == NULL){
                printf("Artista nao encontrado\n");
            }
            else{
                
                printf("Informe o Nome do Album:\n");
                fflush(stdin);
                scanf("%[^\n]", nomeAlbum);

                recebeu = InsereArvNoAlbum(&verifica->albuns, verifica, nomeAlbum);

                if(recebeu == 1){
                    printf("Album Cadastrado Com Sucesso!\n");
                }
                else{
                    printf("Album informado ja esta cadastrado!\n");
                }
            }


            break;
        }
        case 3:{
            
            printf("Nova Musica Chegando...\n");
            printf("Informe o Nome do Artista:\n");
            fflush(stdin);
            scanf("%[^\n]", nomeArtista);

            Artista *sabeArtista;
            sabeArtista = BuscarArtista(&RaizArtista, nomeArtista);

            if(sabeArtista == NULL){
                printf("Artista Nao Encontrado!\n");
            }
            else{
                printf("Informe o Nome do Album:\n");
                fflush(stdin);
                scanf("%[^\n]", nomeAlbum);

                Albuns *sabeAlbum;
                sabeAlbum = BuscarAlbum(&sabeArtista->albuns, nomeAlbum);

                if(sabeAlbum == NULL){
                    printf("O Album Informado Nao Existe\n");
                }

                else{
                    char tituloMusica[200];
                    float minutos;
                    int ver;

                    printf("Informe o Titulo da Musica:\n");
                    fflush(stdin);
                    scanf("%[^\n]", tituloMusica);

                    printf("Informe a Quantidade de Minutos da Musica %s\n", tituloMusica);
                    scanf("%f", &minutos);
                    
                    ver = CadastraMusica(&(sabeAlbum->musica), tituloMusica, minutos);

                    if(ver == 0){
                        printf("A Musica %s Ja Existe no Album %s\n", tituloMusica, nomeAlbum);

                    }
                    else{
                        printf("A Musica %s Foi Cadastrada com Sucesso!\n", tituloMusica);
                      
                    }
                    

                }
                
                
            }

            break;

        }

        case 4:{
            printf("FUNCAO BUSCAR!\n");
            printf("o que deseja buscar?\n");
            printf("1- Artista\n");
            printf("2- Album\n");
            printf("3- Musica\n");

            int op2;

            scanf("%d", &op2);
            if(op2 == 1){
            
                printf("Informe o Nome do Artista:\n");
                fflush(stdin);
                scanf("%[^\n]", nomeArtista);
               
               Artista *verifica;
               verifica = BuscarArtista(&RaizArtista, nomeArtista);

               if (verifica == NULL){
                printf("Artista nao encontrado\n");
               }
               else{
                mostrarDadosArtista(RaizArtista, nomeArtista);
               }
            }
            else if(op2 == 2){
                printf("Informe o Nome do Artista:\n");
                fflush(stdin);
                scanf("%[^\n]", nomeArtista);

                Artista *verifica;
                verifica = BuscarArtista(&RaizArtista, nomeArtista);

                if(verifica == NULL){
                    printf("Artista nao encontrado\n");
                }
                else{
                    printf("Informe o Nome do Album:\n");
                    fflush(stdin);
                    scanf("%[^\n]", nomeAlbum);

                    Albuns *sabeAlbum;
                    sabeAlbum = BuscarAlbum(&verifica->albuns, nomeAlbum);

                    if(sabeAlbum == NULL){
                        printf("Album nao encontrado\n");
                    }
                    else{
                        printf("INFORMACOES DO ALBUM:\n");
                        printf("Nome: %s\n", sabeAlbum->tituloAlbum);
                        printf("Ano: %d\n", sabeAlbum->ano);
                        printf("Quantidade de Musicas: %d\n", sabeAlbum->quantmusica);
                        printf("Artista(s): %s\n", verifica->artista);
                        printf("\n");
                    }
                }
            }
            else if(op2 == 3){

                Artista *arti;
                printf("Informe Primeiro o Nome do Artista:\n");
                fflush(stdin);
                scanf("%[^\n]", nomeArtista);
                arti = BuscarArtista(&RaizArtista, nomeArtista);
                
                if(arti == NULL){
                    printf("Artista Nao Encontrado!\n");

                }

                else{
                    printf("Agora Informe o Nome do Album:\n");
                    fflush(stdin);
                    scanf("%[^\n]", nomeAlbum);

                    Albuns *sabeAlbum;
                    sabeAlbum = BuscarAlbum(&arti->albuns, nomeAlbum);

                    if(sabeAlbum == NULL){
                        printf("Album Nao Encontrado!\n");
                    }

                    else{
                        char musica[200];
                        Musica *aux;
                 
                        printf("Informe o Nome da Musica:\n");
                        fflush(stdin); 
                        scanf("%[^\n]", musica);
                        aux = BuscaMusica(sabeAlbum->musica, musica);

                        if(aux == NULL){
                            printf("Musica Nao Encontrada\n");
                        }
                        else{
                            
                            printf("INFORMACOES DA MUSICA:\n");
                            printf("Nome: %s\n", aux->tituloMusica);
                            printf("Minutos: %.2f\n", aux->minutos);
                            printf("Album que ela se Encontra: %s\n", sabeAlbum->tituloAlbum);
                            printf("Artista(s): %s\n", arti->artista);
                            printf("\n");
                        }
                        
                    }
                }
                
            }
            break;

        }

        case 5:{
            printf("FUNCAO REMOVER!\n");
            printf("o que deseja remover?\n");
            printf("1- Artista\n");
            printf("2- Album\n");
            printf("3- Musica\n");

            int op3;

            scanf("%d", &op3);
            if(op3 == 1){
                char nome[200];
                printf("Informe o Nome do Artista:\n");
                fflush(stdin);
                scanf("%[^\n]", nome);
                if(ArtistaExiste(RaizArtista, nome)){
                    printf("Se voce remover o artista, todos os seus albuns e musicas serao removidos tambem\n");
                    printf("Deseja Continuar?\n");
                    printf("1- Sim\n");
                    printf("2- Nao\n");
                    int op5;
                    scanf("%d", &op5);
                    if(op5 == 1){
                        int sabe = remove_Artista(&RaizArtista, nome);
                        if(sabe==1){
                            printf("Artista removido com sucesso!\n");
                        }
                        else{
                            printf("Nao deu para remover o Artista\n");
                        }

                    }else{
                        printf("operacao cancelada\n");
                    }

                }else{
                    printf("Artista nao encontrado\n");
                }

               
            }
            else if(op3 == 3){
                char nomeArti[200], nomealbum[200];
                printf("Informe o Nome do Artista:\n");
                fflush(stdin);
                scanf("%[^\n]", nomeArti);
                Artista *Arti;
                Arti = BuscarArtista(&RaizArtista, nomeArti);

                if(Arti == NULL){
                    printf("Artista Nao Encontrado\n");
                }
                else{
                    printf("Artista Encotrado!\n");
                    printf("Informe o Nome do Album:\n");
                    fflush(stdin);
                    scanf("%[^\n]", nomealbum);
                    Albuns *RecebeAlbum;
                    RecebeAlbum = BuscarAlbum(&(Arti->albuns), nomealbum);

                    if(RecebeAlbum == NULL){
                        printf("Album Nao Encotrado\n");

                    }
                    else{
                        char nomemusic[200];
                        printf("Album Encontrado\n");
                        printf("Informe o Nome da Musica:\n");
                        fflush(stdin);
                        scanf("%[^\n]", nomemusic);
                    
                        remover_musica(&(RecebeAlbum->musica), nomemusic);

                       
                    }
                }
            }
            
            

            break;
        }
       
        
        case 6:{

            printf("FUNCAO IMPRIMIR!\n");
            printf("qual informacao da arvore deseja imprimir: \n");
            printf("1- Artista\n");
            printf("2- Album\n");
            printf("3- Musica\n");

            int op4;
            scanf("%d", &op4);
            if(op4 == 1){
                printf("artistas cadastrados na arvore: \n");
                imprime(RaizArtista); 
            }
            else if(op4 == 2){
                printf("Informe o Nome do Artista:\n");
                fflush(stdin);
                scanf("%[^\n]", nomeArtista);

                Artista *verifica;
                verifica = BuscarArtista(&RaizArtista, nomeArtista);

                if (verifica == NULL)
                {
                    printf("Artista nao encontrado\n");
                }
                else
                {
                    printf("albuns cadastrados na arvore: \n");
                    imprimeAlbuns(verifica->albuns);
                }
            }
            else if(op4 == 3){
                printf("Informe o Nome do Artista:\n");
                fflush(stdin);
                scanf("%[^\n]", nomeArtista);

                Artista *verifica;
                verifica = BuscarArtista(&RaizArtista, nomeArtista);

                if (verifica == NULL)
                {
                    printf("Artista nao encontrado\n");
                }
                else
                {
                    printf("Informe o Nome do Album:\n");
                    fflush(stdin);
                    scanf("%[^\n]", nomeAlbum);

                    Albuns *sabeAlbum;
                    sabeAlbum = BuscarAlbum(&verifica->albuns, nomeAlbum);

                    if (sabeAlbum == NULL)
                    {
                        printf("Album nao encontrado\n");
                    }
                    else
                    {
                        printf("musicas cadastradas na arvore: \n");
                        imprimeMusica(sabeAlbum->musica);
                    }
                }
            }
            else{
                printf("Opcao Invalida\n");
            }

            break;
        }
        if(op == 7){
            break;
        }
        }

    }
  

  liberaArtista(&RaizArtista);
  return 0;
  
    
    
}