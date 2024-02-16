#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct Musica
{
    char tituloMusica[200];
    float minutos;
    struct Musica *Prox;
} Musica;



typedef struct Albuns
{
    struct Albuns *esq;
    struct Albuns *cen;
    struct Albuns *dir;
    //DADOS DO INFO1
    char tituloAlbum1[200];
    int ano1;
    int quantmusica1;
    struct Musica *musica1;
    //DADOS DO INFO 2
    char tituloAlbum2[200];
    int ano2;
    int quantmusica2;
    struct Musica *musica2;
    int NumdeInfos;

} Albuns;

//titulo, ano, quantimusica

typedef struct Artista
{
    struct Artista *esq;
    struct Artista *cen;
    struct Artista *dir;
    //DADOS DO INFO1
    char TipoArtista1[200];
    char estilomusical1[100];
    char artista1[200];
    int numAlbuns1;
    struct Albuns *albuns1;

    //DADOS DO INFO2
    char TipoArtista2[200];
    char estilomusical2[100];
    char artista2[200];
    int numAlbuns2;
    struct Albuns *albuns2;
    
    int NumdeInfos;

} Artista;

int ehFolha(Artista *Raiz)
{
    return (Raiz->cen == NULL && Raiz->esq == NULL && Raiz->dir == NULL);
}

Artista *criaNo(char *artista1, char *TipoArtista1, char *estilomusical1, int numAlbuns1, Artista *Esq, Artista *Cen, Artista *Dir)
{
    Artista *No;

    No = (struct Artista *)malloc(sizeof(struct Artista));

    strcpy((*No).TipoArtista1, TipoArtista1);
    strcpy((*No).estilomusical1, estilomusical1);
    strcpy((*No).artista1, artista1);
    (*No).numAlbuns1 = numAlbuns1;
    (*No).albuns1 = NULL;


    strcpy((*No).artista2, " ");
    (*No).NumdeInfos = 1;
    (*No).esq = Esq;
    (*No).cen = Cen;
    (*No).dir = Dir;

    return No;
}



void adiciona(Artista **Raiz, char *nomeArtista, char *TipoArtista, char *EstiloMus, int numdeAlbuns, Albuns *Album, Artista *MaiorNo)
{
    if (strcmp(nomeArtista, (*Raiz)->artista1) > 0)
    {
        strcpy((*Raiz)->artista2, nomeArtista);
        strcpy((*Raiz)->TipoArtista2, TipoArtista);
        strcpy((*Raiz)->estilomusical2, EstiloMus);
        (*Raiz)->albuns2 = Album;
        (*Raiz)->numAlbuns2 = numdeAlbuns;
        (*Raiz)->dir = MaiorNo;
    }
    else
    {
        strcpy((*Raiz)->artista2, (*Raiz)->artista1);
        strcpy((*Raiz)->TipoArtista2, (*Raiz)->TipoArtista1);
        strcpy((*Raiz)->estilomusical2, (*Raiz)->estilomusical1);
        (*Raiz)->numAlbuns2 = (*Raiz)->numAlbuns1;
        (*Raiz)->albuns2 = (*Raiz)->albuns1;
       

        strcpy((*Raiz)->artista1, nomeArtista);
        strcpy((*Raiz)->TipoArtista1, TipoArtista);
        strcpy((*Raiz)->estilomusical1, EstiloMus);
        (*Raiz)->numAlbuns1 = numdeAlbuns;
        (*Raiz)->albuns1 = Album;
        (*Raiz)->dir = (*Raiz)->cen;
        (*Raiz)->cen = MaiorNo;
    }

    (*Raiz)->NumdeInfos = 2;
}


 Artista *quebraNo(Artista **Raiz, char *artista, char *TipoArtista, char *estilo, int numAlbuns, Albuns *Album, Albuns **SobeAlbum, char *sobeArtista, char *sobetipoArtista, char *sobeEstilo, int *sobeNumAlbuns, Artista *MaiorNo)
{
    Artista *Novo;
    if (strcmp(artista,(*Raiz)->artista1) < 0)
    {
        // *sobe = (*Raiz)->Info1;
        strcpy(sobeArtista,(*Raiz)->artista1);
        strcpy(sobeEstilo,(*Raiz)->estilomusical1);
        strcpy(sobetipoArtista,(*Raiz)->TipoArtista1);
        *sobeNumAlbuns =(*Raiz)->numAlbuns1;
        *SobeAlbum = (*Raiz)->albuns1;

        Novo = criaNo((*Raiz)->artista2,(*Raiz)->estilomusical2,(*Raiz)->TipoArtista2,(*Raiz)->numAlbuns2, (*Raiz)->cen,(*Raiz)->dir, NULL);
        // (*Raiz)->Info1 = valor;
        strcpy((*Raiz)->artista2, artista);
        strcpy((*Raiz)->estilomusical2, estilo);
        strcpy((*Raiz)->TipoArtista2, TipoArtista);
        (*Raiz)->numAlbuns2 = numAlbuns;
        (*Raiz)->albuns2 = Album;
        (*Raiz)->cen = MaiorNo;
    }
    else if (strcmp(artista, (*Raiz)->artista2) < 0)
    {
        strcpy(sobeArtista, artista);
        strcpy(sobeEstilo, estilo);
        strcpy(sobetipoArtista, TipoArtista);
        *sobeNumAlbuns = numAlbuns;
        *SobeAlbum = Album;
        Novo = criaNo((*Raiz)->artista2, (*Raiz)->estilomusical2, (*Raiz)->TipoArtista2, (*Raiz)->numAlbuns2, MaiorNo, (*Raiz)->dir, NULL);
    }
    else
    {
        strcpy(sobeArtista, (*Raiz)->artista2);
        strcpy(sobeEstilo, (*Raiz)->estilomusical2);
        strcpy(sobetipoArtista, (*Raiz)->TipoArtista2);
        *sobeNumAlbuns = (*Raiz)->numAlbuns2;
        *SobeAlbum = (*Raiz)->albuns2;
        Novo = criaNo(artista, estilo, TipoArtista, numAlbuns, (*Raiz)->dir, MaiorNo, NULL);
    }
    strcpy((*Raiz)->artista2, " ");

 

    (*Raiz)->NumdeInfos = 1;
    (*Raiz)->dir = NULL;

    return (Novo);
}




Artista *inserirArv23(Artista *Pai, Artista **Raiz, char *nomeArtista, char *TipoArtista, char *EstiloMus, int numdeAlbuns, Albuns *Album, Albuns **SobeAlbum, char *sobenome, char *sobetipo, char *sobeestilo, int *sobenumalbuns)
{
    Artista  *maiorNo;
    maiorNo = NULL;
    if (*Raiz == NULL)
        *Raiz = criaNo(nomeArtista, TipoArtista, EstiloMus, numdeAlbuns, NULL, NULL, NULL);
    else
    {
        if (ehFolha(*Raiz))
        {
            if ((*Raiz)->NumdeInfos == 1)
                adiciona(Raiz, nomeArtista, TipoArtista, EstiloMus, numdeAlbuns, Album, maiorNo);
            else // quando não tem espaço
            {
                Artista *novo;
                novo = quebraNo(Raiz, nomeArtista, TipoArtista, EstiloMus, numdeAlbuns, Album, SobeAlbum, sobenome, sobetipo, sobeestilo, sobenumalbuns, maiorNo);
                if (Pai == NULL)
                {
                    Artista *no;
                    no = criaNo(sobenome, sobetipo, sobeestilo, *sobenumalbuns, *Raiz, novo, NULL);
                    *Raiz = no;
                }
                else
                    maiorNo = novo;
            }
        }
        else
        { // quando não é folha
            if (strcmp(nomeArtista, (*Raiz)->artista1) < 0)
                maiorNo = inserirArv23(*Raiz, &((*Raiz)->esq), nomeArtista, TipoArtista, EstiloMus, numdeAlbuns, Album, SobeAlbum, sobenome, sobetipo, sobeestilo, sobenumalbuns);
            else if ((*Raiz)->NumdeInfos == 1 || strcmp(nomeArtista, (*Raiz)->artista2) < 0)
                maiorNo = inserirArv23(*Raiz, &((*Raiz)->cen), nomeArtista, TipoArtista, EstiloMus, numdeAlbuns, Album, SobeAlbum, sobenome, sobetipo, sobeestilo, sobenumalbuns);
            else
                maiorNo = inserirArv23(*Raiz, &((*Raiz)->dir), nomeArtista, TipoArtista, EstiloMus, numdeAlbuns, Album, SobeAlbum, sobenome, sobetipo, sobeestilo, sobenumalbuns);

            if (maiorNo != NULL)
            {
                if ((*Raiz)->NumdeInfos == 1)
                {
                    adiciona(Raiz, sobenome, sobetipo, sobeestilo, *sobenumalbuns, *SobeAlbum,maiorNo);
                    maiorNo = NULL;
                }
                else // quando não tem espaço
                {
                    char *sobeartista1 = (char *)malloc(sizeof(char) * 200), sobetipo1[200], sobeestilo1[200];
                    int sobenumdealbuns1;
                    Artista *novo;
                    Albuns *SobeAlbum1 = NULL;
                    novo = quebraNo(Raiz, sobenome, sobetipo, sobeestilo, *sobenumalbuns, *SobeAlbum, &SobeAlbum1,sobeartista1, sobetipo1, sobeestilo1, &sobenumdealbuns1, maiorNo);
                    if (Pai == NULL)
                    {
                        Artista *no;
                        no = criaNo(sobeartista1, sobetipo1, sobeestilo1, sobenumdealbuns1, *Raiz, novo, NULL);
                        *Raiz = no;
                        maiorNo = NULL;
                    }
                    else
                    {
                        maiorNo = novo;
                        strcpy(sobenome, sobeartista1);
                        strcpy(sobetipo, sobetipo1);
                        strcpy(sobeestilo, sobeestilo1);
                        *SobeAlbum = SobeAlbum1;
                        *sobenumalbuns = sobenumdealbuns1;
                    }
                }
            }
        }
    }

    return maiorNo;
}





void ImprimirArtista(Artista *Raiz){
    if(Raiz != NULL){

        ImprimirArtista(Raiz->esq);
        printf("Nome do Artista: %s\n", Raiz->artista1);
        printf("Estilo Musical do Artista: %s\n", Raiz->estilomusical1);
        printf("Tipo do Artista: %s\n", Raiz->TipoArtista1);
        printf("Quantidade de Albuns do Artista %s: %d\n", Raiz->artista1, Raiz->numAlbuns1);

        ImprimirArtista(Raiz->cen);
        if(Raiz->NumdeInfos == 2){
            printf("Imprimindo o INFO2:\n");
            printf("Nome do Artista: %s\n", Raiz->artista2);
            printf("Estilo Musical do Artista: %s\n", Raiz->estilomusical2);
            printf("Tipo do Artista: %s\n", Raiz->TipoArtista2);
            printf("Quantidade de Albuns do Artista %s: %d\n", Raiz->artista2, Raiz->numAlbuns2);
        }

       
       
        ImprimirArtista(Raiz->dir);
    }
}

Artista *BuscaArtista(Artista **tree, char *nomeArtista)
{
    Artista *NO;
    NO = NULL;
    if (*tree != NULL)
    {
        if (strcmp(nomeArtista, (*tree)->artista1) == 0)
        {
            NO = *tree;
        }
        else if (strcmp(nomeArtista, (*tree)->artista2) == 0)
        {
            NO = *tree;
        }
        else
        {
            if (strcmp(nomeArtista, (*tree)->artista1) < 0)
            {
    
                NO = BuscaArtista(&(*tree)->esq, nomeArtista);
            }
            else if (strcmp(nomeArtista, (*tree)->artista2) < 0 || (*tree)->NumdeInfos == 1)
            {
              
                NO = BuscaArtista(&(*tree)->cen, nomeArtista);
            }
            else
            {
              
                NO = BuscaArtista(&(*tree)->dir, nomeArtista);
            }
        }
    }
    return NO;
}

//CODIGO DE ALBUNS

//titulo, ano, quantimusica

int ehFolhaAlbuns(Albuns *Raiz)
{
    return (Raiz->cen == NULL && Raiz->esq == NULL && Raiz->dir == NULL);


}

Albuns *criaNoAlbum(char *titulo1, int ano1, int quantmusica1, Albuns *esq, Albuns *cen, Albuns *dir)
{
    Albuns *No;

    No = (Albuns *)malloc(sizeof(Albuns));

    strcpy((*No).tituloAlbum1, titulo1);
    (*No).ano1 = ano1;
    (*No).quantmusica1 = quantmusica1;
    (*No).musica1 = NULL;

    strcpy((*No).tituloAlbum2, " ");
    (*No).NumdeInfos = 1;
    (*No).esq = esq;
    (*No).cen = cen;
    (*No).dir = dir;

    return No;

    
}




void adicionaAlbum(Albuns **Raiz, char *titulo, int anoalbum, int quantmusic, Albuns *MaiorNo)
{
    if (strcmp(titulo, (*Raiz)->tituloAlbum1) > 0)
    {
        strcpy((*Raiz)->tituloAlbum2, titulo);
        
        (*Raiz)->ano2 = anoalbum;
        (*Raiz)->quantmusica2 =  quantmusic;
        (*Raiz)->dir = MaiorNo;
    }
    else
    {
        strcpy((*Raiz)->tituloAlbum2, (*Raiz)->tituloAlbum1);
        (*Raiz)->ano2 =  (*Raiz)->ano1;
        (*Raiz)->quantmusica2 = (*Raiz)->quantmusica1;
       
       

        strcpy((*Raiz)->tituloAlbum1, titulo);
        (*Raiz)->ano1 = anoalbum;
        (*Raiz)->quantmusica1 = quantmusic;
      
        (*Raiz)->dir = (*Raiz)->cen;
        (*Raiz)->cen = MaiorNo;
    }

    (*Raiz)->NumdeInfos = 2;
}


Albuns *quebraNoAlbum(Albuns **Raiz, char *titulo, int ano, int quantmusica, char *sobeTitulo, int *sobeAno, int *sobeQuant, Albuns *MaiorNo)
{
    Albuns *Novo;
    if (strcmp(titulo,(*Raiz)->tituloAlbum1) < 0)
    {
        // *sobe = (*Raiz)->Info1;
        strcpy(sobeTitulo,(*Raiz)->tituloAlbum1);
        //strcpy(sobeAno,(*Raiz)->ano1);
        //strcpy(sobeQuant,(*Raiz)->quantmusica1);
        *sobeAno =(*Raiz)->ano1;
        *sobeQuant =(*Raiz)->quantmusica1;


        Novo = criaNoAlbum((*Raiz)->tituloAlbum2,(*Raiz)->ano2,(*Raiz)->quantmusica2,(*Raiz)->cen,(*Raiz)->dir, NULL);
        // (*Raiz)->Info1 = valor;
        strcpy((*Raiz)->tituloAlbum2, titulo);
        //strcpy((*Raiz)->ano2, ano);
        //strcpy((*Raiz)->quantmusica2, quantmusica);
        (*Raiz)->ano2 = ano;
        (*Raiz)->quantmusica2 = quantmusica;
        (*Raiz)->cen = MaiorNo;
    }
    else if (strcmp(titulo, (*Raiz)->tituloAlbum2) < 0)
    {
        strcpy(sobeTitulo, titulo);
        //strcpy(sobeEstilo, estilo);
        //strcpy(sobetipoArtista, TipoArtista);
        *sobeAno = ano;
        *sobeQuant = quantmusica;
        Novo = criaNoAlbum((*Raiz)->tituloAlbum2, (*Raiz)->ano2, (*Raiz)->quantmusica2, MaiorNo, (*Raiz)->dir, NULL);
    }
    else
    {
        strcpy(sobeTitulo, (*Raiz)->tituloAlbum2);
        //strcpy(sobeAno, (*Raiz)->ano2);
        //strcpy(sobetipoArtista, (*Raiz)->TipoArtista2);
        *sobeAno = (*Raiz)->ano2;
        *sobeQuant = (*Raiz)->quantmusica2;
        Novo = criaNoAlbum(titulo, ano, quantmusica, (*Raiz)->dir, MaiorNo, NULL);
    }
    strcpy((*Raiz)->tituloAlbum2, " ");

 

    (*Raiz)->NumdeInfos = 1;
    (*Raiz)->dir = NULL;

    return (Novo);
}


Albuns *inserirArv23Album(Albuns *Pai, Albuns **Raiz, char *titulo, int ano, int quantimusic,  char *sobetitulo, int *sobeano, int *sobequantimusic)
{
    Albuns  *maiorNo;
    maiorNo = NULL;
    if (*Raiz == NULL)
        *Raiz = criaNoAlbum(titulo, ano, quantimusic, NULL, NULL, NULL);
    else
    {
        if (ehFolhaAlbuns(*Raiz))
        {
            if ((*Raiz)->NumdeInfos == 1)
                adicionaAlbum(Raiz, titulo, ano, quantimusic, maiorNo);
            else // quando não tem espaço
            {
                Albuns *novo;
                novo = quebraNoAlbum(Raiz, titulo, ano, quantimusic, sobetitulo, sobeano, sobequantimusic, maiorNo);
                if (Pai == NULL)
                {
                    Albuns *no;
                    no = criaNoAlbum(sobetitulo, *sobeano, *sobequantimusic, *Raiz, novo, NULL);
                    *Raiz = no;
                }
                else
                    maiorNo = novo;
            }
        }
        else
        { //quando não é folha
            if (strcmp(titulo, (*Raiz)->tituloAlbum1) < 0)
                maiorNo = inserirArv23Album(*Raiz, &((*Raiz)->esq), titulo, ano, quantimusic, sobetitulo, sobeano, sobequantimusic);
            else if ((*Raiz)->NumdeInfos == 1 || strcmp(titulo, (*Raiz)->tituloAlbum2) < 0)
                maiorNo = inserirArv23Album(*Raiz, &((*Raiz)->cen), titulo, ano, quantimusic, sobetitulo, sobeano, sobequantimusic);
            else
                maiorNo = inserirArv23Album(*Raiz, &((*Raiz)->dir), titulo, ano, quantimusic, sobetitulo, sobeano, sobequantimusic);

            if (maiorNo != NULL)
            {
                if ((*Raiz)->NumdeInfos == 1)
                {
                    adicionaAlbum(Raiz, sobetitulo, *sobeano, *sobequantimusic, maiorNo);
                    maiorNo = NULL;
                }
                else //quando não tem espaço
                {
                    char *sobetitulo1 = (char *)malloc(sizeof(char) * 200);
                    int sobeano1;
                    int sobequantimusic1;
                    Albuns *novo;
                    novo = quebraNoAlbum(Raiz, sobetitulo, *sobeano, *sobequantimusic, sobetitulo1, &sobeano1, &sobequantimusic1, maiorNo);
                    if (Pai == NULL)
                    {
                        Albuns *no;
                        no = criaNoAlbum(sobetitulo1, sobeano1, sobequantimusic1, *Raiz, novo, NULL);
                        *Raiz = no;
                        maiorNo = NULL;
                    }
                    else
                    {
                        maiorNo = novo;
                        strcpy(sobetitulo, sobetitulo1);
                        *sobeano = sobeano1;
                        *sobequantimusic = sobequantimusic1;
                       
                    }
                }
            }
        }
    }

    return maiorNo;
}



void ImprimirAlbum(Albuns *Raiz){
    if(Raiz != NULL){

        ImprimirAlbum(Raiz->esq);
        printf("Titulo do Album: %s\n", Raiz->tituloAlbum1);
        printf("Ano do Album: %d\n", Raiz->ano1);
        printf("Quantidade de Musicas: %d\n", Raiz->quantmusica1);
       

        ImprimirAlbum(Raiz->cen);
        if(Raiz->NumdeInfos == 2){
            printf("Imprimindo o INFO2:\n");
            printf("Titulo do Album: %s\n", Raiz->tituloAlbum2);
            printf("Ano do Album: %d\n", Raiz->ano2);
            printf("Quantidade de Musicas: %d\n", Raiz->quantmusica2);
        }

       
       
        ImprimirAlbum(Raiz->dir);
    }
}


Albuns *BuscarAlbum(Albuns **raiz, char *nomeAlbum)
{
    Albuns *NO;
    NO = NULL;
    if (*raiz != NULL)
    {
        if (strcmp(nomeAlbum, (*raiz)->tituloAlbum1) == 0)
        {
            NO = *raiz;
        }
        else if (strcmp(nomeAlbum, (*raiz)->tituloAlbum2) == 0)
        {
            NO = *raiz;
        }
        else
        {
            if (strcmp(nomeAlbum, (*raiz)->tituloAlbum1) < 0)
            {
    
                NO = BuscarAlbum(&(*raiz)->esq, nomeAlbum);
            }
            else if (strcmp(nomeAlbum, (*raiz)->tituloAlbum2) < 0 || (*raiz)->NumdeInfos == 1)
            {
              
                NO = BuscarAlbum(&(*raiz)->cen, nomeAlbum);
            }
            else
            {
              
                NO = BuscarAlbum(&(*raiz)->dir, nomeAlbum);
            }
        }
    }
    return NO;
}


int CadastraMusica(Musica **lista, char *TituloMusica, float min){
    int sabe = 1;
    //Verificar se a música já existe na lista
    Musica *aux = *lista;
    while (aux != NULL && sabe != 0) {
        if (strcmp(TituloMusica, aux->tituloMusica) == 0) {
            sabe = 0; 
    
        }
        aux = aux->Prox;
    }

    if(sabe != 0){
    //Se a música não estiver na lista, prossiga com o cadastro
        Musica *novaMusica = (Musica*)malloc(sizeof(Musica));
        
        //GUARDANDO OS DADOS
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

void ImprimeMusicas(Musica *lista) {
    Musica *aux = lista;
    printf("\n");

    while (aux != NULL) {
        printf("Titulo da Musica: %s\n", aux->tituloMusica);
        printf("Duracao: %.2f minutos\n", aux->minutos);
        aux = aux->Prox;
    }
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


void liberarMusica(Musica **Lista){
    if(*Lista != NULL){
        liberarMusica(&((*Lista)->Prox));
        free(*Lista);
        *Lista = NULL;
    }
}

void liberarAlbuns(Albuns **Raiz){
    if(*Raiz != NULL){
        liberarAlbuns(&((*Raiz)->esq));
        liberarAlbuns(&((*Raiz)->cen));
        liberarAlbuns(&((*Raiz)->dir));
        liberarMusica(&((*Raiz)->musica1));
        liberarMusica(&((*Raiz)->musica2));
        free(*Raiz);
        *Raiz = NULL;
    }
}

void liberarArtista(Artista **Raiz){
    if(*Raiz != NULL){
        liberarArtista(&((*Raiz)->esq));
        liberarArtista(&((*Raiz)->cen));
        liberarArtista(&((*Raiz)->dir));
        liberarAlbuns(&((*Raiz)->albuns1));
        liberarAlbuns(&((*Raiz)->albuns2));
        free(*Raiz);
        *Raiz = NULL;
    }
}


int main()
{
    
    Artista *raiz;
    raiz = NULL;

 
    int op;

    while(1){
        printf("======MENU======\n");
        printf("1 - Inserir artista\n");
        printf("2 - Cadastrar Album\n");
        printf("3 - Imprimir Artista\n");
        printf("4 - Imprimir Todos os Albuns de Um Artista\n");
        printf("5 - Imprimir Musicas De Um Album\n");
        printf("6 - Buscar Artista\n");
        printf("7 - Buscar Album\n");
        printf("8 - Buscar Musica\n");
        printf("9 - Remover Musica\n");
        printf("10 - Sair\n");

        scanf("%d", &op);

        switch(op){
            case 1:{
                char nomeArtista[200], TipoArti[200], EstiloMusical[100];
                char sobenome[200], sobetipo[200], sobeestilo[200];
                Albuns *Album = NULL;
                Albuns *SobeAlbum = NULL;


            
                int numAlbum, sobenumalbuns;
            
                printf("Digite o nome do artista: ");
            
                scanf("%s", nomeArtista);
                printf("Digite o tipo de artista: ");
                scanf("%s", TipoArti);
                printf("Digite o estilo musical: ");
                scanf("%s", EstiloMusical);
                printf("Digite o numero de albuns: ");
                scanf("%d", &numAlbum);
                
               
               

                inserirArv23(NULL, &raiz, nomeArtista, TipoArti, EstiloMusical, numAlbum, Album, &SobeAlbum,sobenome, sobetipo, sobeestilo, &sobenumalbuns);
            
                
                
                break;
            }

            case 2:{
                char nomeArt[200];
                printf("Informe o Nome do Artista:\n");
                fflush(stdin);
                scanf("%[^\n]", nomeArt);

                Artista *CadAlbum;

                CadAlbum = BuscaArtista(&raiz, nomeArt);

                if(CadAlbum == NULL){
                    printf("Artista Nao Encontrado\n");
                }
                else{
                    char TituloAlbum[200];
                    int ano, quantimusic;
                    char sobetitulo[200];
                    int sobeano, sobequantimusic;
                    printf("Informe o Titulo do Album:\n");
                    fflush(stdin);
                    scanf("%[^\n]", TituloAlbum);
                    Albuns *Busca1, *Busca2;
                    Busca1 = BuscarAlbum(&(CadAlbum->albuns1), TituloAlbum);
                    Busca2 = BuscarAlbum(&(CadAlbum->albuns2), TituloAlbum);
                    if((Busca1 != NULL || Busca2 != NULL)){
                        printf("Esse Album Ja Existe Para o Artista Informado\n");
                    }
                    else{
                    
                        printf("Informe o Ano:\n");
                        scanf("%d", &ano);

                        printf("Informe a Quantidade de Musica:\n");
                        scanf("%d", &quantimusic);

                        int quantidade = 0;
                        int ver;
                        char nomemusic[200];
                        float minutos;
                        
                        if(strcmp(nomeArt, CadAlbum->artista1) == 0){

                            inserirArv23Album(NULL, &(CadAlbum->albuns1), TituloAlbum, ano, quantimusic, sobetitulo, &sobeano, &sobequantimusic);

                         
                            while(quantidade < CadAlbum->albuns1->quantmusica1){
                                printf("Informe o Titulo da Musica %d:\n", quantidade+1);
                                fflush(stdin);
                                scanf("%[^\n]", nomemusic);
                                printf("Informe o Minuto da Musica %d:\n", quantidade+1);
                                scanf("%f", &minutos);

                                ver = CadastraMusica(&(CadAlbum->albuns1->musica1), nomemusic, minutos);

                                 if(ver == 0){
                                    printf("A Musica %s Ja Existe no Album %s\n", nomemusic, CadAlbum->albuns1->tituloAlbum1);
                                    quantidade--;


                                }
                                else{
                                    printf("A Musica %s Foi Cadastrada com Sucesso!\n", nomemusic);
                                    quantidade++;
                                }


                            }
                            
                        }
                        else if (strcmp(nomeArt, CadAlbum->artista2) == 0){
                            inserirArv23Album(NULL, &(CadAlbum->albuns2), TituloAlbum, ano, quantimusic, sobetitulo, &sobeano, &sobequantimusic);

                             while(quantidade < CadAlbum->albuns1->quantmusica1){
                                printf("Informe o Titulo da Musica %d:\n", quantidade+1);
                                fflush(stdin);
                                scanf("%[^\n]", nomemusic);
                                printf("Informe o Minuto da Musica %d:\n", quantidade+1);
                                scanf("%f", &minutos);

                                ver = CadastraMusica(&(CadAlbum->albuns1->musica1), nomemusic, minutos);

                                 if(ver == 0){
                                    printf("A Musica %s Ja Existe no Album %s\n", nomemusic, CadAlbum->albuns1->tituloAlbum1);
                                    quantidade--;


                                }
                                else{
                                    printf("A Musica %s Foi Cadastrada com Sucesso!\n", nomemusic);
                                    quantidade++;
                                }


                            }


                        }
                    }



                }

                break;
                
            }
            case 3:{
                ImprimirArtista(raiz);
                break;
            }

            case 4:{
                char busca[200];
                printf("Informe o Nome do Artista:\n");
                fflush(stdin);
                scanf("%[^\n]", busca);
                Artista *Buscou;
             
                Buscou = BuscaArtista(&raiz, busca);

                if(Buscou == NULL){
                    printf("Artista nao Encontrado\n");
                }

                else{
                    if(strcmp(busca, Buscou->artista1) == 0){
                        if(Buscou->albuns1 == NULL){
                            printf("Nao Tem Nenhum Album Cadastrado Para Esse Artista\n");
                        }
                        else{
                            ImprimirAlbum(Buscou->albuns1);
                        }

                
                    }
                    else if (strcmp(busca, Buscou->artista2) == 0){
                         if(Buscou->albuns2 == NULL){
                            printf("Nao Tem Nenhum Album Cadastrado Para Esse Artista\n");
                        }
                        else{
                            ImprimirAlbum(Buscou->albuns2);
                        }
                    }
                }
                break;
            }
            case 5:{
                char busca[200], buscaalbum[200];
                printf("Informe o Nome do Artista:\n");
                fflush(stdin);
                scanf("%[^\n]", busca);
                Artista *Buscou;
                Albuns *BuscouAlbum;
                Buscou = BuscaArtista(&raiz, busca);

                if(Buscou == NULL){
                    printf("Artista nao Encontrado\n");
                }

                else{
                    if(strcmp(busca, Buscou->artista1) == 0){
                        printf("Informe o Nome do Album:\n");
                        fflush(stdin);
                        scanf("%[^\n]", buscaalbum);

                        BuscouAlbum = BuscarAlbum(&(Buscou->albuns1), buscaalbum);
                        if(BuscouAlbum == NULL){
                            printf("Album Nao Encotrado\n");
                        }
                        else{
                            printf("MUSICAS:\n");
                            ImprimeMusicas(BuscouAlbum->musica1);
                        }

                
                    }
                    else if (strcmp(busca, Buscou->artista2) == 0){
                        printf("Informe o Nome do Album:\n");
                        fflush(stdin);
                        scanf("%[^\n]", buscaalbum);

                        BuscouAlbum = BuscarAlbum(&(Buscou->albuns2), buscaalbum);
                        if(BuscouAlbum == NULL){
                            printf("Album Nao Encotrado\n");
                        }
                        else{
                            printf("MUSICAS\n");
                            ImprimeMusicas(BuscouAlbum->musica2);
                        }
           
                    }
                }
                break;

            }
            case 6:{
                char busca[200];
                printf("Informe o Nome do Artista:\n");
                scanf("%s", busca);
                Artista *Buscou;
                Buscou = BuscaArtista(&raiz, busca);

                if(Buscou == NULL){
                    printf("Artista nao Encontrado\n");
                }

                else{
                    if(strcmp(busca, Buscou->artista1) == 0){
                        printf("O Artista encontrado esta no INFO1\n");
                        printf("Nome do Artista: %s\n", Buscou->artista1);
                        printf("Estilo Musical: %s\n", Buscou->estilomusical1);
                        printf("Tipo do Artista: %s\n", Buscou->TipoArtista1);
                        printf("Numero de Albuns do %s: %d \n", Buscou->artista1, Buscou->numAlbuns1);
                    }
                    else if (strcmp(busca, Buscou->artista2) == 0){
                        printf("O Artista encontrado esta no INFO2\n");
                        printf("Nome do Artista: %s\n", Buscou->artista2);
                        printf("Estilo Musical: %s\n", Buscou->estilomusical2);
                        printf("Tipo do Artista: %s\n", Buscou->TipoArtista2);
                        printf("Numero de Albuns do %s: %d \n", Buscou->artista2, Buscou->numAlbuns2);
                    }
                }
                break;
            }

            case 7:{
                char nomeArtista[200];
                char nomeAlbum[200];
                printf("Informe o Nome do Artista:\n");
                fflush(stdin);
                scanf("%[^\n]", nomeArtista);

                Artista *verifica;
                verifica = BuscaArtista(&raiz, nomeArtista);

                if(verifica == NULL){
                    printf("Artista nao encontrado\n");
                }
                else{
                    printf("Informe o Nome do Album:\n");
                    fflush(stdin);
                    scanf("%[^\n]", nomeAlbum);

                    Albuns *sabeAlbum;
                    if(strcmp(nomeArtista, verifica->artista1) == 0){
                        sabeAlbum = BuscarAlbum(&(verifica->albuns1), nomeAlbum);

                        if(sabeAlbum == NULL){
                        printf("Album nao encontrado\n");
                        }
                        else{
                            printf("INFORMACOES DO ALBUM:\n");
                            printf("Nome: %s\n", sabeAlbum->tituloAlbum1);
                            printf("Ano: %d\n", sabeAlbum->ano1);
                            printf("Quantidade de Musicas: %d\n", sabeAlbum->quantmusica1);
                            printf("Artista(s): %s\n", verifica->artista1);
                            printf("\n");
                        }

                    }

                    else if(strcmp(nomeArtista, verifica->artista2) == 0){

                        sabeAlbum = BuscarAlbum(&(verifica->albuns2), nomeAlbum);
                        if(sabeAlbum == NULL){
                        printf("Album nao encontrado\n");
                        }
                        else{
                            printf("INFORMACOES DO ALBUM:\n");
                            printf("Nome: %s\n", sabeAlbum->tituloAlbum2);
                            printf("Ano: %d\n", sabeAlbum->ano2);
                            printf("Quantidade de Musicas: %d\n", sabeAlbum->quantmusica2);
                            printf("Artista(s): %s\n", verifica->artista2);
                            printf("\n");
                        }

                    }
                    

                    
                
                }

                break;
            }
            case 8:{
                char nomeArtista[200];
                char nomeAlbum[200];
                char nomeMusica[200];
                printf("Informe o Nome do Artista:\n");
                fflush(stdin);
                scanf("%[^\n]", nomeArtista);

                Artista *verifica;
                Musica *BuscaM;
                verifica = BuscaArtista(&raiz, nomeArtista);

                if(verifica == NULL){
                    printf("Artista nao encontrado\n");
                }
                else{
                    printf("Informe o Nome do Album:\n");
                    fflush(stdin);
                    scanf("%[^\n]", nomeAlbum);

                    Albuns *sabeAlbum;
                    if(strcmp(nomeArtista, verifica->artista1) == 0){
                        sabeAlbum = BuscarAlbum(&(verifica->albuns1), nomeAlbum);

                        if(sabeAlbum == NULL){
                        printf("Album nao encontrado\n");
                        }
                        else{
                            printf("Informe o Nome da Musica:\n");
                            fflush(stdin);
                            scanf("%[^\n]", nomeAlbum);
                           BuscaM =  BuscaMusica(sabeAlbum->musica1, nomeMusica);
                            
                            if(BuscaM == NULL){
                                printf("Musica Nao Encontrada no Album %s do Artista %s\n", sabeAlbum->tituloAlbum1, verifica->artista1);
                            }
                            else{
                                printf("Informacoes da Musica:\n");
                                ImprimeMusicas(BuscaM);
                                printf("Nome do Artista: %s\n", verifica->artista1);
                                printf("Album: %s\n",  sabeAlbum->tituloAlbum1);
                            }
                        }

                    }

                    else if(strcmp(nomeArtista, verifica->artista2) == 0){
                        sabeAlbum = BuscarAlbum(&(verifica->albuns2), nomeAlbum);

                        if(sabeAlbum == NULL){
                        printf("Album nao encontrado\n");
                        }
                        else{
                            printf("Informe o Nome da Musica:\n");
                            fflush(stdin);
                            scanf("%[^\n]", nomeAlbum);
                            BuscaM = BuscaMusica(sabeAlbum->musica2, nomeMusica);
                            
                            if(BuscaM == NULL){
                                printf("Musica Nao Encontrada no Album %s do Artista %s\n", sabeAlbum->tituloAlbum2, verifica->artista2);
                            }
                            else{
                                printf("Informacoes da Musica:\n");
                                ImprimeMusicas(BuscaM);
                                printf("Nome do Artista: %s\n", verifica->artista2);
                                printf("Album: %s\n",  sabeAlbum->tituloAlbum2);
                            }
                        }
               
                    }
                    

                    
                
                }

                break;
            }

            case 9:{
                char nomeArtista[200];
                char nomeAlbum[200];
                char nomeMusica[200];
                printf("Informe o Nome do Artista:\n");
                fflush(stdin);
                scanf("%[^\n]", nomeArtista);

                Artista *verifica;
         
                verifica = BuscaArtista(&raiz, nomeArtista);

                if(verifica == NULL){
                    printf("Artista nao encontrado\n");
                }
                else{
                    printf("Informe o Nome do Album:\n");
                    fflush(stdin);
                    scanf("%[^\n]", nomeAlbum);

                    Albuns *sabeAlbum;
                    if(strcmp(nomeArtista, verifica->artista1) == 0){
                        sabeAlbum = BuscarAlbum(&(verifica->albuns1), nomeAlbum);

                        if(sabeAlbum == NULL){
                        printf("Album nao encontrado\n");
                        }
                        else{
                            printf("Informe o Nome da Musica:\n");
                            fflush(stdin);
                            scanf("%[^\n]", nomeAlbum);
                            remover_musica(&(sabeAlbum->musica1), nomeMusica);
                            
                        }

                    }

                    else if(strcmp(nomeArtista, verifica->artista2) == 0){
                        sabeAlbum = BuscarAlbum(&(verifica->albuns2), nomeAlbum);

                        if(sabeAlbum == NULL){
                        printf("Album nao encontrado\n");
                        }
                        else{
                            printf("Informe o Nome da Musica:\n");
                            fflush(stdin);
                            scanf("%[^\n]", nomeAlbum);
                            remover_musica(&(sabeAlbum->musica2), nomeMusica);
                            
                        }
               
                    }
                    

                    
                
                }

                break;

            }


        }

    }
    
    liberarArtista(&raiz);
    printf("Memoria Liberada\n");
    
    return 0;
}