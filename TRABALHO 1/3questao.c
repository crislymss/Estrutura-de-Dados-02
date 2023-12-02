#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Participantes{
    char nomeArtista[100];
    char nomePerso[100];
    char descricaoPerso[250];
    struct Participantes *Prox;
}Participantes;


typedef struct DadosTemporadas{
    int NumdaTemp;
    char tituTemp[100];
    int quantEp;
    int ano;
    int altura;
}DadosTemporadas;

typedef struct Temporadas{
    struct DadosTemporadas Info;
    struct Temporadas *Esq;
    struct Temporadas *Dir;
    struct Participantes *Parti;
    
}Temporadas;

typedef struct Series{
   int cod;
   char titulo[100];
   struct Series *Esq;
   struct Series *Dir;
   struct Temporadas *Temp;
   int altura;
}Series;

int AlturadaArvoredeSerie(Series *raiz)
{
   int altura = 0;
   if (raiz != NULL)
   {
       int altura_esquerda = AlturadaArvoredeSerie(raiz->Esq);
       int altura_direita = AlturadaArvoredeSerie(raiz->Dir);
       altura = (altura_esquerda > altura_direita ? altura_esquerda : altura_direita) + 1;
   }
   return altura;
}


void rotacaoDireitaSerie(Series **raiz)
{
   Series *aux; //declara um ponteiro aux de Serie
   aux = (*raiz)->Esq; //aux vai receber o no esquerdo da raiz
   (*raiz)->Esq = aux->Dir;  //esquerda da raiz vai receber a direita do aux
   aux->Dir = (*raiz); //direita do aux recebe a raiz
   (*raiz)->altura = AlturadaArvoredeSerie(*raiz); // atualiza a altura da arvore
   aux->altura = AlturadaArvoredeSerie(aux); //atualiza a altura do aux
   *raiz = aux; //a raiz recebe o aux
}

void rotacaoEsquerdaSerie(Series **raiz)
{
   Series *aux; //declara um ponteiro aux
   aux = (*raiz)->Dir; //aux vai receber o nó esquerdo da raiz
   (*raiz)->Dir = aux->Esq; //nó direito da raiz vai receber pro nó esquerdo do aux
   aux->Esq = (*raiz); // no esquerdo aux recebe a raiz
   (*raiz)->altura = AlturadaArvoredeSerie(*raiz); //atualizar a altura da arvore
   aux->altura = AlturadaArvoredeSerie(aux); //atualizar a altura do aux
   *raiz = aux; //faz a raiz receber o aux
}


int inserirArvAVLSerie(Series **raiz, Series *no)
{
   int inseriu = 1;

   if (*raiz == NULL)
   {
       *raiz = no;
       (*raiz)->Esq = NULL;
       (*raiz)->Dir = NULL;
       (*raiz)->altura = 1;
   }
   else if (no->cod < (*raiz)->cod)
   {
       inseriu = inserirArvAVLSerie(&((*raiz)->Esq), no);
   }
   else if (no->cod > (*raiz)->cod)
   {
       inseriu = inserirArvAVLSerie(&((*raiz)->Dir), no);
   }
   else
   {
       inseriu = 0;
   }

   if (inseriu){
       (*raiz)->altura = 1 + max(AlturadaArvoredeSerie((*raiz)->Esq), AlturadaArvoredeSerie((*raiz)->Dir));

       int FB = AlturadaArvoredeSerie((*raiz)->Esq) - AlturadaArvoredeSerie((*raiz)->Dir);

       if (FB > 1 && no->cod < (*raiz)->Esq->cod){
           rotacaoDireitaSerie(raiz);
       }

       else if (FB < -1 && no->cod > (*raiz)->Dir->cod){
           rotacaoEsquerdaSerie(raiz);
       }

        else if (FB > 1 && no->cod > (*raiz)->Esq->cod){
            rotacaoEsquerdaSerie(&((*raiz)->Esq));
            rotacaoDireitaSerie(raiz);
        }

       else if (FB < -1 && no->cod < (*raiz)->Dir->cod)
       {
           rotacaoDireitaSerie(&((*raiz)->Dir));
           rotacaoEsquerdaSerie(raiz);
       }
   }



   return inseriu;
}

int AlturadaArvoredeTemp(Temporadas *raiz){
   int altura = 0;
   if (raiz != NULL)
   {
       int altura_esquerda = AlturadaArvoredeTemp(raiz->Esq);
       int altura_direita = AlturadaArvoredeTemp(raiz->Dir);
       altura = (altura_esquerda > altura_direita ? altura_esquerda : altura_direita) + 1;
   }
   return altura;
}

void rotacaoDireitaTemp(Temporadas **raiz){
   Temporadas *aux;
   aux = (*raiz)->Esq;
   (*raiz)->Esq = aux->Dir;
   aux->Dir = (*raiz);
   (*raiz)->Info.altura = AlturadaArvoredeTemp(*raiz); 
   aux->Info.altura = AlturadaArvoredeTemp(aux);
   *raiz = aux;
}


void rotacaoEsquerdaTemp(Temporadas **raiz){
   Temporadas *aux;
   aux = (*raiz)->Dir;
   (*raiz)->Dir = aux->Esq;
   aux->Esq = (*raiz);
   (*raiz)->Info.altura = AlturadaArvoredeTemp(*raiz);
   aux->Info.altura = AlturadaArvoredeTemp(aux);
   *raiz = aux;
}


void inserirArvAVLTemp(Temporadas **raiz, Temporadas *no)
{


   if (*raiz == NULL)
   {
       *raiz = no;
       (*raiz)->Esq = NULL;
       (*raiz)->Dir = NULL;
       (*raiz)->Info.altura= 1;
   }
   else if (no->Info.NumdaTemp < (*raiz)->Info.NumdaTemp){
       inserirArvAVLTemp(&((*raiz)->Esq), no);
   }
   else if (no->Info.NumdaTemp > (*raiz)->Info.NumdaTemp){
       inserirArvAVLTemp(&((*raiz)->Dir), no);
   }


       (*raiz)->Info.altura = 1 + max(AlturadaArvoredeTemp((*raiz)->Esq), AlturadaArvoredeTemp((*raiz)->Dir));

       int FB = AlturadaArvoredeTemp((*raiz)->Esq) - AlturadaArvoredeTemp((*raiz)->Dir);

       if (FB > 1 && no->Info.NumdaTemp < (*raiz)->Esq->Info.NumdaTemp){
           rotacaoDireitaTemp(raiz);
       }
       else if (FB < -1 && no->Info.NumdaTemp > (*raiz)->Dir->Info.NumdaTemp)
       {
           rotacaoEsquerdaTemp(raiz);
       }
       else if (FB > 1 && no->Info.NumdaTemp > (*raiz)->Esq->Info.NumdaTemp)
       {
           rotacaoEsquerdaTemp(&((*raiz)->Esq));
           rotacaoDireitaTemp(raiz);
       }
       else if (FB < -1 && no->Info.NumdaTemp < (*raiz)->Dir->Info.NumdaTemp)
       {
           rotacaoDireitaTemp(&((*raiz)->Dir));
           rotacaoEsquerdaTemp(raiz);
       }
 

}


void inserirParticipantes(Participantes **lista) {
    Participantes *novoParti = (Participantes*)malloc(sizeof(Participantes));
    
    printf("Informe o Nome do Artista:\n");
    fflush(stdin);
    scanf("%[^\n]", novoParti->nomeArtista);
    printf("Informe o Nome do Personagem:\n");
    fflush(stdin);
    scanf("%[^\n]", novoParti->nomePerso);
    printf("Informe a Descricao do Personagem:\n");
    fflush(stdin);
    scanf("%[^\n]", novoParti->descricaoPerso);
    
    novoParti->Prox = NULL;  

    if (*lista == NULL) {
        *lista = novoParti;
    } 
    else {
        Participantes *aux = *lista;
        Participantes *ant = NULL;
        
        while (aux != NULL && strcmp(novoParti->nomeArtista, aux->nomeArtista) > 0) { //percorre a lista ate encontrar o local do no a ser inserido com base na ordem alfabetica do nome dos artistas
            ant = aux;
            aux = aux->Prox;
        }

        if (ant == NULL) {
            novoParti->Prox = *lista;
            *lista = novoParti;
        }
        else {
            ant->Prox = novoParti;
            novoParti->Prox = aux;
        }
    }
}


int contaTemp(Temporadas *raiz){
    int cont=0;
    if(raiz != NULL){
        cont += 1;
        cont += contaTemp(raiz->Esq);
        cont += contaTemp(raiz->Dir);
    }

    return cont;
}  

   
void imprimirSeries(Series *raiz){
    int numTemp;
    if(raiz != NULL){
        imprimirSeries(raiz->Esq);
        printf("Codigo da Serie: %d\n", raiz->cod);
        printf("Titulo da Serie: %s\n", raiz->titulo);
        numTemp = contaTemp(raiz->Temp);
        printf("Numero de Temporadas: %d\n", numTemp);
        imprimirSeries(raiz->Dir);
    }
}

void chamaParticipantes(Participantes *lista, int codTemp){
    Participantes *aux;
    int cont = 1;
    aux = lista;
    printf("Participantes da %d Temporada:\n", codTemp);
    while(aux != NULL){
        printf("Informacoes do %d Participante:\n", cont);
        printf("Nome do Artista: %s\n", aux->nomeArtista);
        printf("Nome do Personagem: %s\n", aux->nomePerso);
        printf("Descricao do Personagem: %s\n", aux->descricaoPerso);
        printf("\n");
        aux = aux->Prox;
        cont++;
    }
}


void chamaTemporadas(Temporadas *raiz){
 
    if(raiz!=NULL){
        printf("Numero da Temporada: %d\n", raiz->Info.NumdaTemp);
        printf("Nome da Temporada: %s\n", raiz->Info.tituTemp);
        printf("Quantidade de Episodios: %d\n", raiz->Info.quantEp);
        printf("\n");
        chamaParticipantes(raiz->Parti, raiz->Info.NumdaTemp);
        chamaTemporadas(raiz->Esq);
        chamaTemporadas(raiz->Dir);

    }
}

void mostraDadosTemps(Series *raiz, int codigo){
   if(raiz != NULL){
        if(raiz->cod == codigo){
            chamaTemporadas(raiz->Temp);
        
        }
        mostraDadosTemps(raiz->Esq, codigo);
        mostraDadosTemps(raiz->Dir, codigo);

    }
}

void ImprimirPartiTemp(Participantes *lista){
    	
    Participantes *aux = lista;
    do{
        printf("Nome do Personagem: %s\n", aux->nomePerso);
        aux = aux->Prox;
    }while(aux != NULL);
}

void ProcuraTemp(Temporadas *raiz, int numTemp){
    if(raiz != NULL){
        if(raiz->Info.NumdaTemp == numTemp){
            ImprimirPartiTemp(raiz->Parti);

        }

        ProcuraTemp(raiz->Esq, numTemp);
        ProcuraTemp(raiz->Dir, numTemp);
    }
}


void ImprimirPersonagemSerie(Series *raiz, int codSerie, int numTemp){
    if(raiz != NULL){
        if(raiz->cod == codSerie){
            ProcuraTemp(raiz->Temp, numTemp);
        }

        ImprimirPersonagemSerie(raiz->Esq, codSerie, numTemp);
        ImprimirPersonagemSerie(raiz->Dir, codSerie, numTemp);
    }
}


Series *BuscarSerie(Series **raiz, int cod) {
    Series *aux = NULL;
    if (*raiz != NULL) {
        if ((*raiz)->cod == cod) {
            aux = *raiz;
        } else {
            aux = BuscarSerie(&((*raiz)->Esq), cod);
            if (aux == NULL) {
                aux = BuscarSerie(&((*raiz)->Dir), cod);
            }
        }
    }
    return aux;
}

void imprimirArtistasPorPersonagem(Series *raiz){



    Temporadas *temporada = raiz->Temp;
    char personagemEncontrado[100]; 

        
    personagemEncontrado[0] = '\0';

    int todasTemporadas = 1; 

    while (temporada != NULL){
        Participantes *participante = temporada->Parti;

        while (participante != NULL){
            if (personagemEncontrado[0] == '\0'){
                strcpy(personagemEncontrado, participante->nomePerso);
            }
            else if (strcmp(personagemEncontrado, participante->nomePerso) != 0){
                    
                todasTemporadas = 0;
                break;
            }

            participante = participante->Prox;
        }

        if (todasTemporadas == 0){
            break; 
        }

        temporada = temporada->Dir;
    }

    if (todasTemporadas == 1){
        temporada = raiz->Temp;
        printf("Artistas que interpretaram o personagem %s na serie %s em todas as temporadas:\n", personagemEncontrado, raiz->titulo);

        while (temporada != NULL){
            Participantes *participante = temporada->Parti;

            while (participante != NULL){
                if (strcmp(personagemEncontrado, participante->nomePerso) == 0){
                    printf("- %s\n", participante->nomeArtista);
                }
                participante = participante->Prox;
            }

            temporada = temporada->Dir;
            }
    }
    else{
        printf("Personagem Nao Encontrado Em Todas As Temporadas da Serie.\n");
    }
    

}


int ExisteTemporada(Temporadas *raiz, int codigo){
    int existe = 0;
    if(raiz != NULL){
        if(raiz->Info.NumdaTemp == codigo){
            existe = 1;
        }
        if(existe != 1){
            existe = ExisteTemporada(raiz->Esq, codigo);
        }
        if(existe != 1){
            existe = ExisteTemporada(raiz->Dir, codigo);
        }
    }
    return existe;
}


int main(){
    Series *raizSeries = NULL;

    

    int escolha;
    do{
    printf("\n");
    printf("1 - Cadastrar Serie.\n");
    printf("2 - Cadastrar Temporada.\n");
    printf("3 - Imprimir series.\n");
    printf("4 - Imprimir os dados de todas as temporadas de uma serie.\n");
    printf("5 - Imprimir  todos  os  personagens  de  uma  determinada  temporada.\n");
    printf("6 - Imprimir  o  nome  de  todos  os  artistas  que  interpretaram  um  determinado  personagem  em  todas  as temporadas.\n");
    printf("7 - Sair\n");
    printf("\n");
    printf("Escolha uma opcao:\n");
    scanf("%d", &escolha);

    switch (escolha)
    {
    case 1:{
  
        int recebeu;
        Series *novaSerie;
        novaSerie = (Series*)malloc(sizeof(Series));
        printf("Informe o Codigo da Serie:\n");
        scanf("%d", &(novaSerie->cod));
        printf("Informe o Titulo da Serie:\n");
        fflush(stdin);
        scanf("%[^\n]", novaSerie->titulo); 
       
        novaSerie->Temp = NULL;


        recebeu = inserirArvAVLSerie(&raizSeries, novaSerie);


        if(recebeu == 1){
            printf("Serie Cadastrada Com Sucesso!\n");
        }
        else{
            printf("O Codigo da Serie Informado Ja Existe!\n");
        }
        
        break;
    }

   case 2:{
        if(raizSeries == NULL){
            printf("Nenhuma Serie Cadastrada No Momento!\n");
        }
        else{
            int CodSerie, numTemp;
            
            printf("Informe o Codigo da Serie:\n");
            scanf("%d", &CodSerie);
            printf("Buscando Serie...\n");
            printf("\n");
            Series *recebeSerie;
            recebeSerie = BuscarSerie(&raizSeries, CodSerie);
            if(recebeSerie != NULL){
                printf("Serie Encontrada Com Sucesso!\n");
                printf("Informe o Numero da Temporada:\n");
                scanf("%d", &numTemp);
                int sabeTemp;
                sabeTemp = ExisteTemporada(recebeSerie->Temp, numTemp);
                if(sabeTemp == 1){
                    printf("O Numero da Temporada Informado Ja Existe!\n");
                }
                else{
                    Participantes *participantes;
                    participantes = NULL;
                    Temporadas *novaTemp;
                    novaTemp = (Temporadas*)malloc(sizeof(Temporadas));
                    novaTemp->Info.NumdaTemp = numTemp;
                    printf("Informe o Titulo da Temporada %d:\n", numTemp);
                    fflush(stdin);
                    scanf("%[^\n]", novaTemp->Info.tituTemp);
                    printf("Informe a Quantidade de Episodios:\n");
                    scanf("%d", &(novaTemp->Info.quantEp));
                    printf("Informe o Ano da Temporada:\n");
                    scanf("%d", &(novaTemp->Info.ano));
                    int inserirperso =0;
                    int contParti = 1;
                    do{
                    printf("Digite as Informacoes do Participante %d:\n", contParti);
                    inserirParticipantes(&participantes);
                    printf("Deseja Inserir Mais um Participante (1 - SIM 2 - NAO)\n");
                    scanf("%d", &inserirperso);
                    contParti++;
                    }while(inserirperso !=2);

                    novaTemp->Parti = participantes;
                    inserirArvAVLtemp(&recebeSerie->Temp, novaTemp);
                    printf("Temporada Cadastrada Com Sucesso!\n");
                
                }
            
                


            }
            else{
                printf("Serie Nao Encontrada!\n");
            } 
        }  

        break;
    }

    case 3:{
        if(raizSeries == NULL){
            printf("Nenhuma Serie Cadastrada No Momento!\n");
        }
        else{
        imprimirSeries(raizSeries);
        }
        break;
    }
    case 4:{
        if(raizSeries == NULL){
            printf("Nenhuma Serie Cadastrada No Momento!\n");
        }
        else{
            int codSerie;
            printf("Informe o Codigo da Serie:\n");
            scanf("%d", &codSerie);
            
            Series *verifica;
            verifica = BuscarSerie(&raizSeries, codSerie);

            if(verifica == NULL){
                printf("Serie Nao Encotrada!\n");
            }
            else if(verifica->Temp == NULL){
                printf("Nenhuma Temporada Cadastrada Para Essa Serie!\n");
            }
            else{
    
                mostraDadosTemps(raizSeries, codSerie);
            }
        }
        break;
    }
    case 5:{
        if(raizSeries == NULL){
            printf("Nenhuma Serie Cadastrada No Momento!\n");
        }
        else{
            int codSerie, codTemp;
            printf("Informe o Codigo da Serie:\n");
            scanf("%d", &codSerie);
            Series *verificaSerie;
            verificaSerie = BuscarSerie(&raizSeries, codSerie);

            if(verificaSerie == NULL){
                printf("Serie Nao Encotrada!\n");
            }
            else if(verificaSerie->Temp == NULL){
                printf("Nenhuma Temporada Cadastrada Para Essa Serie!\n");
            }
            else{
                int tem;
                printf("Informe o Codigo da Temporada:\n");
                scanf("%d", &codTemp);
                tem = ExisteTemporada(verificaSerie->Temp, codTemp);
                if(tem == 0){
                    printf("Temporada Nao Encotrada!\n");
                }
                else{
                ImprimirPersonagemSerie(raizSeries, codSerie, codTemp);
                }
            }
        }
        break;
    }


    case 6:{

        if(raizSeries == NULL){
            printf("Nenhuma Serie Cadastrada no Momento!\n");
        }
        else{
        int codSerie;
        printf("Informe o Codigo da Serie:\n");
        scanf("%d", &codSerie);
        Series *Procura;
        Procura = BuscarSerie(&raizSeries, codSerie);
        if(Procura == NULL){
            printf("Serie Nao Encotrada!\n");
        }
        else if(Procura->Temp == NULL){
            printf("Nenhuma Temporada Cadastrada Para Essa Serie!\n");
        }
        else{
            imprimirArtistasPorPersonagem(Procura);
        }
        }
        break;
        
    }

    default:
        break;
    }
    }while(escolha != 7);
    printf("Programa Finalizado!\n");
    
    free(raizSeries);
    return 0;


}