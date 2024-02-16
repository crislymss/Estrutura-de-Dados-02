#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

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
    // DADOS DO INFO1
    char tituloAlbum1[200];
    int ano1;
    int quantmusica1;
    struct Musica *musica1;
    // DADOS DO INFO 2
    char tituloAlbum2[200];
    int ano2;
    int quantmusica2;
    struct Musica *musica2;
    int NumdeInfos;

} Albuns;

// titulo, ano, quantimusica

typedef struct Artista
{
    struct Artista *esq;
    struct Artista *cen;
    struct Artista *dir;
    // DADOS DO INFO1
    char TipoArtista1[200];
    char estilomusical1[100];
    char artista1[200];
    int numAlbuns1;
    struct Albuns *albuns1;

    // DADOS DO INFO2
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
    if (strcmp(artista, (*Raiz)->artista1) < 0)
    {
        // *sobe = (*Raiz)->Info1;
        strcpy(sobeArtista, (*Raiz)->artista1);
        strcpy(sobeEstilo, (*Raiz)->estilomusical1);
        strcpy(sobetipoArtista, (*Raiz)->TipoArtista1);
        *sobeNumAlbuns = (*Raiz)->numAlbuns1;
        *SobeAlbum = (*Raiz)->albuns1;

        Novo = criaNo((*Raiz)->artista2, (*Raiz)->estilomusical2, (*Raiz)->TipoArtista2, (*Raiz)->numAlbuns2, (*Raiz)->cen, (*Raiz)->dir, NULL);
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
    Artista *maiorNo;
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
                    adiciona(Raiz, sobenome, sobetipo, sobeestilo, *sobenumalbuns, *SobeAlbum, maiorNo);
                    maiorNo = NULL;
                }
                else // quando não tem espaço
                {
                    char *sobeartista1 = (char *)malloc(sizeof(char) * 200), sobetipo1[200], sobeestilo1[200];
                    int sobenumdealbuns1;
                    Artista *novo;
                    Albuns *SobeAlbum1 = NULL;
                    novo = quebraNo(Raiz, sobenome, sobetipo, sobeestilo, *sobenumalbuns, *SobeAlbum, &SobeAlbum1, sobeartista1, sobetipo1, sobeestilo1, &sobenumdealbuns1, maiorNo);
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

void ImprimirArtista(Artista *Raiz)
{
    if (Raiz != NULL)
    {

        ImprimirArtista(Raiz->esq);
        printf("Nome do Artista: %s\n", Raiz->artista1);
        printf("Estilo Musical do Artista: %s\n", Raiz->estilomusical1);
        printf("Tipo do Artista: %s\n", Raiz->TipoArtista1);
        printf("Quantidade de Albuns do Artista %s: %d\n", Raiz->artista1, Raiz->numAlbuns1);

        ImprimirArtista(Raiz->cen);
        if (Raiz->NumdeInfos == 2)
        {
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

// CODIGO DE ALBUNS

// titulo, ano, quantimusica

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
        (*Raiz)->quantmusica2 = quantmusic;
        (*Raiz)->dir = MaiorNo;
    }
    else
    {
        strcpy((*Raiz)->tituloAlbum2, (*Raiz)->tituloAlbum1);
        (*Raiz)->ano2 = (*Raiz)->ano1;
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
    if (strcmp(titulo, (*Raiz)->tituloAlbum1) < 0)
    {
        // *sobe = (*Raiz)->Info1;
        strcpy(sobeTitulo, (*Raiz)->tituloAlbum1);
        // strcpy(sobeAno,(*Raiz)->ano1);
        // strcpy(sobeQuant,(*Raiz)->quantmusica1);
        *sobeAno = (*Raiz)->ano1;
        *sobeQuant = (*Raiz)->quantmusica1;

        Novo = criaNoAlbum((*Raiz)->tituloAlbum2, (*Raiz)->ano2, (*Raiz)->quantmusica2, (*Raiz)->cen, (*Raiz)->dir, NULL);
        // (*Raiz)->Info1 = valor;
        strcpy((*Raiz)->tituloAlbum2, titulo);
        // strcpy((*Raiz)->ano2, ano);
        // strcpy((*Raiz)->quantmusica2, quantmusica);
        (*Raiz)->ano2 = ano;
        (*Raiz)->quantmusica2 = quantmusica;
        (*Raiz)->cen = MaiorNo;
    }
    else if (strcmp(titulo, (*Raiz)->tituloAlbum2) < 0)
    {
        strcpy(sobeTitulo, titulo);
        // strcpy(sobeEstilo, estilo);
        // strcpy(sobetipoArtista, TipoArtista);
        *sobeAno = ano;
        *sobeQuant = quantmusica;
        Novo = criaNoAlbum((*Raiz)->tituloAlbum2, (*Raiz)->ano2, (*Raiz)->quantmusica2, MaiorNo, (*Raiz)->dir, NULL);
    }
    else
    {
        strcpy(sobeTitulo, (*Raiz)->tituloAlbum2);
        // strcpy(sobeAno, (*Raiz)->ano2);
        // strcpy(sobetipoArtista, (*Raiz)->TipoArtista2);
        *sobeAno = (*Raiz)->ano2;
        *sobeQuant = (*Raiz)->quantmusica2;
        Novo = criaNoAlbum(titulo, ano, quantmusica, (*Raiz)->dir, MaiorNo, NULL);
    }
    strcpy((*Raiz)->tituloAlbum2, " ");

    (*Raiz)->NumdeInfos = 1;
    (*Raiz)->dir = NULL;

    return (Novo);
}

Albuns *inserirArv23Album(Albuns *Pai, Albuns **Raiz, char *titulo, int ano, int quantimusic, char *sobetitulo, int *sobeano, int *sobequantimusic)
{
    Albuns *maiorNo;
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
        { // quando não é folha
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
                else // quando não tem espaço
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

void ImprimirAlbum(Albuns *Raiz)
{
    if (Raiz != NULL)
    {

        ImprimirAlbum(Raiz->esq);
        printf("Titulo do Album: %s\n", Raiz->tituloAlbum1);
        printf("Ano do Album: %d\n", Raiz->ano1);
        printf("Quantidade de Musicas: %d\n", Raiz->quantmusica1);

        ImprimirAlbum(Raiz->cen);
        if (Raiz->NumdeInfos == 2)
        {
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

int CadastraMusica(Musica **lista, char *TituloMusica, float min)
{
    int sabe = 1;

    Musica *aux = *lista;
    while (aux != NULL && sabe != 0)
    {
        if (strcmp(TituloMusica, aux->tituloMusica) == 0)
        {
            sabe = 0;
        }
        aux = aux->Prox;
    }

    if (sabe != 0)
    {
        
        Musica *novaMusica = (Musica *)malloc(sizeof(Musica));

        // GUARDANDO OS DADOS
        strcpy(novaMusica->tituloMusica, TituloMusica);
        novaMusica->minutos = min;

        novaMusica->Prox = NULL;

        if (*lista == NULL)
        {
            *lista = novaMusica;
        }
        else
        {
            Musica *aux = *lista;
            Musica *ant = NULL;

            while (aux != NULL && strcmp(novaMusica->tituloMusica, aux->tituloMusica) > 0)
            {
                ant = aux;
                aux = aux->Prox;
            }

            if (ant == NULL)
            {
                novaMusica->Prox = *lista;
                *lista = novaMusica;
            }
            else
            {
                ant->Prox = novaMusica;
                novaMusica->Prox = aux;
            }
        }
    }

    return sabe;
}

Musica *BuscaMusica(Musica *lista, char *TituloMusica)
{
    Musica *aux = lista;

    // Percorra a lista
    while (aux != NULL)
    {
        if (strcmp(TituloMusica, aux->tituloMusica) == 0)
        {
            return aux; 
        }
        aux = aux->Prox;
    }


    return NULL;
}

void ImprimeMusicas(Musica *lista)
{
    Musica *aux = lista;
    printf("\n");

    while (aux != NULL)
    {
        printf("Titulo da Musica: %s\n", aux->tituloMusica);
        printf("Duracao: %.2f minutos\n", aux->minutos);
        aux = aux->Prox;
    }
}

Artista **buscaTestes(Artista **raiz, char *nome)
{
    Artista **NO;
    NO = NULL;
    if (*raiz != NULL)
    {
        if (strcmp(nome, (*raiz)->artista1) == 0)
        {
            NO = raiz;
        }
        else if ((*raiz)->NumdeInfos == 2 && strcmp(nome, (*raiz)->artista2) == 0)
        {
            NO = raiz;
        }
        else
        {
            if (strcmp(nome, (*raiz)->artista1) < 0)
            {
               
                NO = buscaTestes(&(*raiz)->esq, nome);
            }
            else if ((*raiz)->NumdeInfos == 1 || strcmp(nome, (*raiz)->artista2) < 0)
            {
              
                NO = buscaTestes(&(*raiz)->cen, nome);
            }
            else
            {
             
                NO = buscaTestes(&(*raiz)->dir, nome);
            }
        }
    }
    return NO;
}

int main()
{
   
    Artista *raiz = NULL;
    double elapsed_nanos;
    double soma = 0;

    

   
    char *artistas[30] = {
        "Ana", "Beatriz", "Carlos", "Daniel", "Eduardo", "Fernanda", "Gabriel", "Helena", "Igor",
        "Julia", "Kleber", "Laura", "Marcos", "Natalia", "Otavio", "Patricia", "Quirino", "Rafael",
        "Sabrina", "Tiago", "Ursula", "Vitor", "Wagner", "Ximena", "Yasmin", "Zacarias",
        "Alice", "Bruno", "Cecilia", "Diego"};


    for (int i = 0; i < 30; i++)
    {

        LARGE_INTEGER start, end, frequency;

        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);

     
        Artista **resultado = buscaTestes(&raiz, artistas[i]);

      
        QueryPerformanceCounter(&end);

    
        elapsed_nanos = ((end.QuadPart - start.QuadPart) * 1.0 / frequency.QuadPart) * 1000000000;
        printf("Tempo de execucao: %.2f nanossegundos da %d Execucao Com o nome %s\n", elapsed_nanos, i + 1, artistas[i]);
        soma += elapsed_nanos;

     
        if (resultado != NULL)
        {
            printf("Caminho percorrido para encontrar '%s': ", artistas[i]);
            
           
        }
    }

    
    printf("Tempo total de execucao: %.2f nanossegundos\n", soma);

    return 0;
}
