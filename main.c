#include <stdio.h>
#include <stdlib.h>


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

int main(){
	Vagas vagas;

    criarListaVagas(&vagas);

    for(int i = 10; i < 35; i++){
        ocuparVagas(&vagas, 0, i);
    }

    mostrarVagas(vagas);

}

void criarListaVagas(Vagas *vagas) {
    vagas -> inicio = NULL;
    vagas -> fim = NULL;
}

int ocuparVagas(Vagas *vagas, int *ocup, int *numVaga){
    struct nodeVaga *aux;
    aux = (struct nodeVaga*) malloc (sizeof(struct nodeVaga));

    if(aux == NULL){
        return 0;
    }

    aux -> ocup = ocup;
    aux -> numVaga = numVaga;

    if(vagas -> inicio == NULL){
		vagas -> inicio = aux;
		vagas -> fim = aux;
	}else {
		vagas -> fim -> prox = aux;
		vagas -> fim = aux;
	}
}

void mostrarVagas(Vagas vagas){
    struct nodeVaga *aux;

    if(vagas.inicio == NULL){
        printf("Lista vazia...\n\n");
    }else {
        aux = vagas.inicio;
        int contador = 0;

        do {
            if(contador % 5 == 0){
                printf("\n\n");
            }


            if(aux -> ocup == 0){
                printf(" | ");
                
                printf("\033[0;32m");
                printf("%d", aux -> numVaga);
                printf("\033[0m");

                printf(" | ");
            }else {
                printf(" | ");

                printf("\033[0;31m");
                printf("%d", aux -> numVaga);
                printf("\033[0m");
                
                printf(" | ");
            }
            
            aux = aux -> prox;

            

            contador++;
        }while(aux != NULL);
    }
}