#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct nodeVaga{
    int ocup;
    int numVaga;
    struct nodeVaga *prox;
};

typedef struct {
    struct nodeVaga *inicio;
    struct nodeVaga *fim;
} Vagas;

void criarListaVagas(Vagas *vagas);
int ocuparVagas(Vagas *vagas, int *ocup, int *numVaga);
void mostrarVagas(Vagas vagas);
void usarVagas(Vagas vagas, int valor);
void liberarVagas(Vagas vagas, int valor);
int entrarCarro();
int sairCarro(Vagas *vagas);

int contadorVagas = 0;

int main(){
    Vagas vagas;

    int opcaoMenu;
    int valor = 0;

    criarListaVagas(&vagas);

    for (int i = 1; i < 11; i++){
        ocuparVagas(&vagas, 0, i);
    }

    do{
        printf("\n\n** MENU OPCOES **");
        printf("\n1- Mostrar vagas disponiveis");
        printf("\n2- Entrada de carro");
        printf("\n3- Saida de carro");
        printf("\n4- Fim");

        printf("\nDigite a sua opcao: ");
     
        scanf("%d", &opcaoMenu);

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
        default:
            printf("\nOpcao invalida!");
        }
    } while (opcaoMenu != 4);
}

void criarListaVagas(Vagas *vagas){
    vagas->inicio = NULL;
    vagas->fim = NULL;
}

int ocuparVagas(Vagas *vagas, int *ocup, int *numVaga){
    struct nodeVaga *aux;
    aux = (struct nodeVaga *)malloc(sizeof(struct nodeVaga));

    if (aux == NULL){
        return 0;
    }

    aux->ocup = ocup;
    aux->numVaga = numVaga;

    if (vagas->inicio == NULL){
        vagas->inicio = aux;
        vagas->fim = aux;
    } else {
        vagas->fim->prox = aux;
        vagas->fim = aux;
    }
}

void mostrarVagas(Vagas vagas){
    struct nodeVaga *aux;

    if (vagas.inicio == NULL){
        printf("Lista vazia...\n\n");
    } else {
        
 
        aux = vagas.inicio;
        int contador = 0;

        do{
            if (contador % 5 == 0){
                printf("\n\n");
            }

            if (aux->ocup == 0){
                printf(" | ");

                printf("\033[0;32m");
                if (aux->numVaga < 10)
                    printf("0%d", aux->numVaga);
                else
                    printf("%d", aux->numVaga);
                printf("\033[0m");

                printf(" | ");
            } else{

                printf(" | ");

                printf("\033[0;31m");
                if (aux->numVaga < 10)
                    printf("0%d", aux->numVaga);
                else
                    printf("%d", aux->numVaga);
                printf("\033[0m");

                printf(" | ");
            }

            aux = aux->prox;

            contador++;
        } while (aux != NULL);
    }
}

void usarVagas(Vagas vagas, int valor){
    struct nodeVaga *aux;

    if (vagas.inicio == NULL){
        printf("Lista vazia...\n\n");
    } else {
        
        printf("\n\n%d", valor);
        aux = vagas.inicio;
        int contador = 0;

        if(contadorVagas == 10){
            printf("Estacionamento Lotado!!!\n");
            return;
        }

        do{
            if (aux->numVaga == valor && aux -> ocup == 0 && contadorVagas < 10){
                contadorVagas ++;
                printf("Contador Vagas: %d", contadorVagas);
                aux->ocup = 1;
            }else if(aux->numVaga == valor && aux -> ocup == 1){
                usarVagas(vagas, entrarCarro());
                break;
            }

            aux = aux->prox;

            contador++;
        } while (aux != NULL);
    }
}

void liberarVagas(Vagas vagas, int valor){
    struct nodeVaga *aux;

    if (vagas.inicio == NULL){
        printf("Lista vazia...\n\n");
    } else {
        
        printf("\n\n%d", valor);
        aux = vagas.inicio;
        int contador = 0;

        if(contadorVagas == 0){
            printf("Estacionamento vazio!!!\n");
            return;
        }

        do{
            if (aux->numVaga == valor && aux -> ocup == 1 && contadorVagas > 0){
                contadorVagas --;
                printf("Contador Vagas: %d", contadorVagas);
                aux->ocup = 0;
            }else if(aux->numVaga == valor && aux -> ocup == 0){
                liberarVagas(vagas, entrarCarro());
                break;
            }

            aux = aux->prox;

            contador++;
        } while (aux != NULL);
    }
}

int entrarCarro(){
    int valor;
 
    srand(clock());
    valor = (rand() % 10) + 1;

    printf("%d\n", valor);

    return valor;
}