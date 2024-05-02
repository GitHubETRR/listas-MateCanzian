/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define MAX_AL 30
#define salir 3
typedef struct competidores{
    char nombre[30];
    int edad;
    struct competidores *next;
}competidores_t;

competidores_t * equipo=NULL; //crea una lista vacía %s le ingresas un string
void menu(void); //listo
void liberar_memoria(void); //listo
void ingresar_competidores(void); //listo
void pedir_datos(competidores_t *competidores); //listo
void ver_equipo(void); //lsito
void imprimir_competidores(competidores_t);

int main(void){
    menu();
    liberar_memoria();
    return 0;
}

void liberar_memoria(void){
    competidores_t *aux=NULL;
    while(equipo!=NULL){
        aux=equipo;
        equipo=equipo->next;
        free(aux);
    }
}

void menu(void){
    int opcion;
    do{
        printf("1. Ingresar competidores\n");
        printf("2. Ver los competidores ingresados en el equipo\n");
        printf("3. Cerrar el menu\n");
        scanf("%d", &opcion);
        if (opcion == 1){
           ingresar_competidores(); 
        }
        if (opcion==2){
            ver_equipo();
        }
    }while(opcion!=salir);
}

void ingresar_competidores(){
    competidores_t * competidores_aux;
    competidores_aux=malloc(sizeof(competidores_t)); //malloc le asigna la cantidad de bites que necesito asignarle a la memoria
    if(competidores_aux==NULL){
        printf("Out of memory\n");
    }else{
        pedir_datos(competidores_aux);
        competidores_aux->next=equipo;
        equipo=competidores_aux;
    }
}

void pedir_datos(competidores_t *competidores){
    printf("Ingresa el nombre del competidor del equipo:\n");
    scanf("%s", competidores->nombre);
    printf("Ingresa la edad del competidor del equipo:\n");
    scanf("%d", &(competidores->edad)); //el & es porque el scanf() necesita la posición para poder cambiar el valor
}

void ver_equipo(){
    competidores_t *competidores=equipo;
    while(competidores!=NULL){
        imprimir_competidores(*competidores);
        competidores=competidores->next;
    }
}

void imprimir_competidores(competidores_t competidores){
    printf("\n---------------\n");
    printf("|Nombre: %s|\n",competidores.nombre);
    printf("|Edad: %d|\n",competidores.edad);
    printf("---------------\n");
}


