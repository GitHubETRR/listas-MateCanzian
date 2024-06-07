/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_AL 30
#define SALIR 3

typedef struct competidores {
    char nombre[30];
    int edad;
    int puntaje;
    struct competidores *next;
} competidores_t;

competidores_t *equipo = NULL; //crea una lista vacía %s le ingresas un string

void menu(void);
void liberar_memoria(void);//listo
void ingresar_competidores(void);//listo
void pedir_datos(competidores_t *competidores);//listo
void ver_equipo(void);//listo
void imprimir_competidores(competidores_t competidores);//listo
void asignar_puntajes(void);//listo (esta es la función nueva)
void ordenar_por_puntaje(void); // función nueva para ordenar los competidores

FILE *archivo1;
int main(void) {
    archivo1 = fopen("Lista de competidores", "wt");
    if (archivo1 == NULL) {
        printf("error");
        exit(1);
    }
    menu();
    liberar_memoria();
    fclose(archivo1);
    return 0;
}

void liberar_memoria(void) {
    competidores_t *aux = NULL;
    while (equipo != NULL) {
        aux = equipo;
        equipo = equipo->next;
        free(aux);
    }
}

void menu(void) {
    int opcion;
    do {
        printf("1. Ingresar competidores\n");
        printf("2. Ver los competidores ingresados en el equipo\n");
        printf("3. Cerrar el menu\n");
        scanf("%d", &opcion);
        if (opcion == 1) {
            ingresar_competidores();
            asignar_puntajes(); // Asignar puntajes después de ingresar competidores
            ordenar_por_puntaje(); // Ordenar los competidores después de asignar sus puntajes (antes de mostrar la lista)
        }
        if (opcion == 2) {
            ver_equipo();
        }
    } while (opcion != SALIR);
}

void ingresar_competidores() {
    competidores_t *competidores_aux;
    competidores_aux = malloc(sizeof(competidores_t)); //malloc le asigna la cantidad de bytes que necesito asignarle a la memoria
    if (competidores_aux == NULL) {
        printf("Out of memory\n");
    } else {
        pedir_datos(competidores_aux);
        competidores_aux->next = equipo;
        equipo = competidores_aux;
    }
}

void pedir_datos(competidores_t *competidores) {
    printf("Ingresa el nombre del competidor del equipo:\n");
    scanf("%s", competidores->nombre);
    printf("Ingresa la edad del competidor del equipo:\n");
    scanf("%d", &(competidores->edad)); // El & es porque el scanf() necesita la posición para poder cambiar el valor
    competidores->puntaje = 0; // Inicializar el puntaje a 0
}

void ver_equipo() {
    competidores_t *competidores = equipo;
    while (competidores != NULL) {
        imprimir_competidores(*competidores);
        competidores = competidores->next;
    }
}

void imprimir_competidores(competidores_t competidores) {
    printf("\n---------------\n");
    printf("| Nombre: %s |\n", competidores.nombre);
    printf("| Edad: %d |\n", competidores.edad);
    printf("| Puntaje: %d |\n", competidores.puntaje);
    printf("---------------\n");
    
    fprintf(archivo1, "\n---------------\n");
    fprintf(archivo1, "|Nombre: %s|\n", competidores.nombre);
    fprintf(archivo1, "|Edad: %d|\n", competidores.edad);
    fprintf(archivo1, "| Puntaje: %d |\n", competidores.puntaje);
    fprintf(archivo1, "---------------\n");
}

void asignar_puntajes() {
    competidores_t *competidor1 = equipo;
    competidores_t *competidor2;
    
    while (competidor1 != NULL) {
        competidor1->puntaje = 0; // Reiniciar el puntaje
        competidor2 = equipo;
        while (competidor2 != NULL) {
            if (competidor1->edad > competidor2->edad) {
                competidor1->puntaje++;
            }
            competidor2 = competidor2->next;
        }
        competidor1 = competidor1->next;
    } /*creo competidor1 y competidor2 para asignar los valores de puntaje arrancando inicialmente en 0 
       y cambiando el puntero de ambos según sea el orden de los competidores ingresados*/
}

void ordenar_por_puntaje() { //Tomo la lista equipo y la reorganiza en orden descendente según el puntaje
    if (equipo == NULL) {
        return;
    } //si la lista equipo vale NULL no ordenamos nada porque no hay competidores cargados

    competidores_t *ordenado = NULL;
    competidores_t *actual = equipo;
    while (actual != NULL) {
        competidores_t *siguiente = actual->next;

        if (ordenado == NULL || actual->puntaje > ordenado->puntaje) { //si la lista ordenanda es igual a NULL o la lista equipo siendo (competidores_t *actual) es mayor a la lista ordenada
            actual->next = ordenado; //el siguiente al actual tendrá el valor de ordenado
            ordenado = actual; //establezco el valor de actual como el valor del nuevo ordenado
        } else {
            competidores_t *aux = ordenado;
            while (aux->next != NULL && aux->next->puntaje >= actual->puntaje) { //se terminan de ordenar los competidores
                aux = aux->next;
            } /*mientras el siguiente en la lista de aux no sea NULL y el puntaje del siguiente de aux sea >= (mayor o igual) al puntaje actual
                aux tomará el valor del siguiente en la lista*/
            actual->next = aux->next;
            aux->next = actual;
        }

        actual = siguiente;
    }
    equipo = ordenado;
}

