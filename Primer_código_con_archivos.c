/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main(){
    FILE* archivo;
    archivo = fopen("Archivo_1.txt", "wt");
    fputs("Hola, este es el archivo 1\n", archivo);
    fclose(archivo);
    printf("Proceso terminado");
}
