#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define TAM 150 //150
int quantFunc = 1000;
typedef struct
{
    char matricula[7];
    char nome[50];
    char funcao[50];
    float salario;
} Funcionario;

typedef struct
{
    Funcionario *tabela[TAM];
    int colisoes;
} TabelaHash;

int hash(char matricula[7])
{
    char chave[7];
    sprintf(chave, "%c%c%s", matricula[4], matricula[5], matricula);
    int d2 = chave[1] - '0';
    int d4 = chave[3] - '0';
    int d6 = chave[5] - '0';
    int valor_hash = d2 * 100 + d4 * 10 + d6;
    int posicao = valor_hash % TAM;
    return posicao;
}

void inserir_funcionario(TabelaHash *tabela, char *matricula, char *nome, char *funcao, float salario)
{
    int posicao = hash(matricula);
    int primeiro_digito = matricula[0] - '0';

    int posicao_remover = -1;

   
    if (tabela->tabela[posicao] != NULL)
    {
        tabela->colisoes++;
        int posicao_inicial = posicao;

      
        while (tabela->tabela[posicao] != NULL){
            if (posicao_remover == -1 && tabela->tabela[posicao] != NULL){
                posicao_remover = posicao;
            }

           posicao = (posicao + primeiro_digito) % TAM; 

            if (posicao == posicao_inicial){
                
                if (tabela->tabela[posicao_remover] != NULL){
                    printf("A chave %s foi removida da posicao %d\n", tabela->tabela[posicao_remover]->matricula, posicao_remover);
                    free(tabela->tabela[posicao_remover]);
                    tabela->tabela[posicao_remover] = NULL;
                }
                break;
            }
        }
    }


    tabela->tabela[posicao] = malloc(sizeof(Funcionario));


    strcpy(tabela->tabela[posicao]->matricula, matricula);
    strcpy(tabela->tabela[posicao]->nome, nome);
    strcpy(tabela->tabela[posicao]->funcao, funcao);
    tabela->tabela[posicao]->salario = salario;

    printf("A chave %s foi inserida na posicao %d\n", matricula, posicao);
}



void mostrar_funcionarios_inseridos(TabelaHash *tabela)
{
    printf("Funcionarios inseridos:\n");
    for (int i = 0; i < TAM; i++)
    {
        if (tabela->tabela[i] != NULL)
        {
            printf("Matricula: %s\n", tabela->tabela[i]->matricula);
            printf("Nome: %s\n", tabela->tabela[i]->nome);
            printf("Funcao: %s\n", tabela->tabela[i]->funcao);
            printf("Salario: %.2f\n", tabela->tabela[i]->salario);
            printf("Posicao: %d\n", i);
            printf("------------------------\n");
        }
    }
}


//FUNCAO TESTE PARA SABER SE ESTAVA INSERINDO CORRETAMENTE 


/*void buscar_funcionario(TabelaHash *tabela, char *nome)
{
    int encontrado = 0; 

    for (int i = 0; i < TAM; i++)
    {
        if (tabela->tabela[i] != NULL && strcmp(tabela->tabela[i]->nome, nome) == 0)
        {
            printf("Funcionario Encotrado:\n");
            printf("Matricula: %s\n", tabela->tabela[i]->matricula);
            printf("Nome: %s\n", tabela->tabela[i]->nome);
            printf("Funcao: %s\n", tabela->tabela[i]->funcao);
            printf("Salario: %.2f\n", tabela->tabela[i]->salario);
            printf("Posicao: %d\n", i);

            encontrado = 1; 
            break;  
        }
    }

    if (encontrado == 0){
        printf("Funcionario com nome %s nao encontrado.\n", nome);
    }
}*/




void liberar_memoria(TabelaHash *tabela)
{
    for (int i = 0; i < TAM; i++)
    {
        if (tabela->tabela[i] != NULL)
        {
            free(tabela->tabela[i]);
        }
    }
}

char* matricula_aleatoria() {
    char* matricula = malloc(7 * sizeof(char));

    for (int i = 0; i < 6; i++) {
        matricula[i] = '0' + rand() % 10;
    }
    matricula[6] = '\0';

    return matricula;
}

void funcionarios_aleatorios(TabelaHash *tabela) {
    for (int i = 0; i < 1000; i++) {
        char* matricula = matricula_aleatoria();
        char* nome = "Aleatorio";
        char* funcao = "Aleatorio";
        float salario = 5000.0; 
        inserir_funcionario(tabela, matricula, nome, funcao, salario);
        quantFunc -= 1;
        free(matricula);
    }
}

int main()
{
    TabelaHash tabela;
    int i;

    tabela.colisoes = 0;
    for (i = 0; i < TAM; i++)
        tabela.tabela[i] = NULL;

    char continuar_programa = 's';

    //AQUI SE DIZ RESPEITO AO TESTE
    srand(time(NULL));  

    funcionarios_aleatorios(&tabela);
    printf("Numero de Colisoes: %d\n", tabela.colisoes);

    while (continuar_programa == 's' || continuar_programa == 'S')
    {
        int opcao;

        printf("\nMenu:\n");
        printf("1 - Cadastrar funcionarios\n");
        printf("2 - Buscar funcionario\n");
        printf("3 - Mostrar todos os funcionarios\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);


        switch (opcao)
        {
        case 1:{
            if(quantFunc == 0){
                printf("Atingido o Limite de Cadastramento dos Funcionarios\n");
            }
            else{
                char matricula[7];
                char nome[50];
                char funcao[50];
                float salario;

                do {
                    printf("Informe a matricula do funcionario (6 digitos): ");
                    scanf("%s", matricula); 
                    getchar();
                } while (strlen(matricula) != 6); 

                printf("Informe o Nome: ");
                fflush(stdin);
                scanf("%[^\n]", nome);

                printf("Informe a Funcao: ");
                fflush(stdin);
                scanf("%[^\n]", funcao);

                printf("Informe o Salario: ");
                scanf("%f", &salario);
            

                inserir_funcionario(&tabela, matricula, nome, funcao, salario);
                
            }
            break;
        }

        /* case 2:{
       
            char nome[50];
            printf("Informe o nome do funcionario: ");
            fflush(stdin);
            scanf("%[^\n]", nome);
            printf("\n");
            buscar_funcionario(&tabela, nome);
            break;
        }*/
        case 3:
            printf("\n");
            mostrar_funcionarios_inseridos(&tabela);
            break;
        case 4:
            continuar_programa = 'n';
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    }
    printf("Liberando Memoria\n");
    liberar_memoria(&tabela);


    return 0;
}
