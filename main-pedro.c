// INCLUSÃO DAS BIBLIOTECAS NECESSÁRIAS PARA O PROJETO
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// // VARIAVEIS GLOBAIS
// char dataSistema[15];
// char horaEntrada[15];

char horaSaida [15];
int number, contadorVagas = 0;
// char *retorno;

// STRUCT REFERENTE A VAGA
struct nodeVaga
{
    int ocup;
    int numVaga;
    char dataSistema[15];
    char horaEntrada[15];
    struct nodeVaga *prox;
};



typedef struct
{
    struct nodeVaga *inicio;
    struct nodeVaga *fim;
} Vagas;

// PROTÓTIPOS DAS FUNÇÕES UTILIZADAS
void criarListaVagas(Vagas *vagas);
int ocuparVagas(Vagas *vagas, int ocup, int numVaga, char *data, char *horaEntrada);
void mostrarVagas(Vagas vagas);
void usarVagas(Vagas vagas, int valor);
void liberarVagas(Vagas vagas, int valor);
int entrarCarro();

// FUNÇÃO PARA FORMATAÇÃO DA HORA
char *format(int number);
// FUNÇÃO PARA RETORNAR A DATA
char *data();
// FUNÇÃO PARA RETORNAR A HORA
char *hora();

int main(){
    Vagas vagas;

    int opcaoMenu;

    criarListaVagas(&vagas);

    for (int i = 1; i < 11; i++){
        ocuparVagas(&vagas, 0, i, "00/00/0000", "00:00:00");
    }

//    struct nodeVaga * aux = vagas.inicio;
//    while (aux) {
//        printf("%d %d %s %s %lx\n", aux->ocup, aux->numVaga, aux->dataSistema, aux->horaEntrada, (long int)aux->prox);
//    }

    do{
        printf("\n\n** MENU OPCOES **");
        printf("\n1- Mostrar vagas disponiveis");
        printf("\n2- Entrada de carro");
        printf("\n3- Saida de carro");
        printf("\n4- Fim");

        printf("\n\nDigite a sua opcao: ");

        scanf("%d", &opcaoMenu);
        fflush(stdin);

        printf("Opcao: %d", opcaoMenu);

        switch (opcaoMenu){
            

            case 1:
                mostrarVagas(vagas);
                break;
            case 2:
                usarVagas(vagas, entrarCarro());
                mostrarVagas(vagas);
                break;
            case 3:
                liberarVagas(vagas, entrarCarro());
                mostrarVagas(vagas);
                break;

            case 4: 
                printf("\n\nPrograma Encerrado!\n\n");
                break;

            default:
                printf("\nOpcao invalida!");
                break;
        }

        
    } while (opcaoMenu != 4);
}

void criarListaVagas(Vagas *vagas)
{
    vagas->inicio = NULL;
    vagas->fim = NULL;
}

int ocuparVagas(Vagas *vagas, int ocup, int numVaga, char *data, char *horaEntrada){
    struct nodeVaga *aux;
    aux = (struct nodeVaga *)malloc(sizeof(struct nodeVaga));

    if (aux == NULL){
        return 0;
    }

    //Armazenando os valores na lista
    aux->ocup = ocup;
    aux->numVaga = numVaga;
    strcpy(aux->dataSistema, data);
    strcpy(aux->horaEntrada, horaEntrada);
    aux->prox = NULL;
    

    if (vagas->inicio == NULL){
        vagas->inicio = aux;
        vagas->fim = aux;
    }else{
        vagas->fim->prox = aux;
        vagas->fim = aux;
    }

    return 1;
}

// FUNÇÃO PARA FORMATAR HORA
char *format(int number){
    char *retorno, ret[15];

    if (number < 15){
        sprintf(ret, "%d", number);
        retorno = ret;
        return retorno;
    }else{
        sprintf(ret, "%d", number);
        retorno = ret;
        return retorno;
    }
}

char dataFormatada[15];
char horarioFormatado[15];

// FUNÇÃO PARA RETORNAR DATA
char *data(){

    int dia, mes, ano;
    char diaFormatado[5], mesFormatado[5], anoFormatado[5], *dataPtr;
    struct tm *local;
    time_t t;

    t = time(NULL);
    local = localtime(&t);

    dia = local->tm_mday;
    mes = local->tm_mon + 1;
    ano = local->tm_year + 1900;



    //Formatando dia/mes/ano
    sprintf(diaFormatado, "%s", format(dia));
    sprintf(mesFormatado, "%s", format(mes)); 
    sprintf(anoFormatado, "%s", format(ano));


    //Juntando o dia/mes/ano <- nesse formato
    sprintf(dataFormatada, "%s/%s/%s", diaFormatado, mesFormatado, anoFormatado);

    // RETORNAR DATA NO FORMATO CORRETO
    dataPtr = dataFormatada;
    return dataPtr;
}

// FUNÇÃO PARA RETORNAR HORA
char *hora(){

    int hora, minuto;
    char horaFormatada[15], minutoFormatado[15], *retorno;

    struct tm *local;
    time_t t;

    t = time(NULL);
    local = localtime(&t);

    // OBTER HORA,MIN E SEG ALOCANDO NA VARIAVEL PONTEIRO
    hora = local->tm_hour;
    minuto = local->tm_min;

    // CONVERTER VALORES PARA TIPO CHAR
    sprintf(horaFormatada, "%s", format(hora));
    sprintf(minutoFormatado, "%s", format(minuto));

    // CRIA VARIAVEL DE RETORNO DOS DADOS E CRIA UM PONTEIRO
    sprintf(horarioFormatado, "%s:%s", horaFormatada, minutoFormatado);

    // RETORNA HORA NO FORMATO CORRETO
    retorno = horarioFormatado;
    return retorno;
}


void mostrarVagas(Vagas vagas){
    struct nodeVaga *aux;

    if (vagas.inicio == NULL){
        printf("Lista vazia...\n\n");
    }else{
        //printf("\n1\n");

        aux = vagas.inicio;
        int contador = 0;

        do{

            if (contador % 5 == 0){
                printf("\n\n");
            }

            if (aux->ocup == 0){
                printf(" | ");

                printf("\033[0;32m");

                if (aux->numVaga < 10){
                    printf("0%d", aux->numVaga);
                }else {
                    printf("%d", aux->numVaga);
                }  
                printf("\033[0m");

                printf(" | ");
            }else if(aux -> ocup == 1){

                printf(" | ");

                printf("\033[0;31m");
                if (aux->numVaga < 10){
                    printf("0%d", aux->numVaga);
                } else {
                    printf("%d", aux->numVaga);
                }
                    
                printf("\033[0m");

                printf(" | ");
            }

            aux = aux->prox;

            
            contador++;

            // if(aux == NULL) {
            //     printf("Final");
            // }

        } while (aux != NULL);

        // printf("\n\n");
        // printf("\n1\n");
    }
}

void usarVagas(Vagas vagas, int valor){
    struct nodeVaga *aux;

    if (vagas.inicio == NULL){
        printf("Lista vazia...\n\n");
    }else{
        aux = vagas.inicio;

        if (contadorVagas == 10){
            printf("Estacionamento Lotado!!!\n");
            return;
        }

        do{
            if (aux->numVaga == valor && aux->ocup == 0 && contadorVagas < 15){
                contadorVagas++;
                
                aux->ocup = 1;
                strcpy(aux->dataSistema, data());
                strcpy(aux->horaEntrada, hora());

                printf("Data: %s\n", aux -> dataSistema);
                printf("Entrou: %s\n", aux -> horaEntrada);

break;
            }else if (aux->numVaga == valor && aux->ocup == 1){
                  valor = entrarCarro();
                aux = vagas.inicio;
              
            } else aux = aux->prox;


        } while (aux != NULL);
    }
}

void liberarVagas(Vagas vagas, int valor){
    struct nodeVaga *aux;

    if (vagas.inicio == NULL){
        printf("Lista vazia...\n\n");
    }else{

        // printf("\n\n%d", valor);
        aux = vagas.inicio;

        if (contadorVagas == 0){
            printf("Estacionamento vazio!!!\n");
            return;
        }

        do{
            if (aux->numVaga == valor && aux->ocup == 1 && contadorVagas > 0){
                contadorVagas--;

                sprintf(horaSaida, "%s", hora());

                printf("Data: %s\n", aux -> dataSistema);
                printf("Entrou: %s\n", aux -> horaEntrada);
                printf("Saiu: %s\n", horaSaida);
                
                aux->ocup = 0;

                break;
            }else if (aux->numVaga == valor && aux->ocup == 0){
                valor = entrarCarro();
                aux = vagas.inicio;
              
            } else aux = aux->prox;

        } while (aux != NULL);
    }
}

int entrarCarro(){
    int valor;

    srand(clock());
    valor = (rand() % 10) + 1;

    return valor;
}
