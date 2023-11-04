#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

int main() {
    char frase[] = "tres tristes tigres trigaban trigo por culpa del bolivar";
    char *m[100]; // Declarar un arreglo de punteros a palabras
    char p1[100] = ""; // Declarar un arreglo para la primera parte
    char p2[100] = ""; // Declarar un arreglo para la segunda parte

    char *token = strtok(frase, " ");
    int num = 0;

    while (token != NULL) {
        m[num++] = token;
        token = strtok(NULL, " ");
    }
    #pragma omp parallel for
    for (int i = 0; i < num; i++) {
        if (i % 2 == 0) {
            #pragma omp critical
            // Agregar la palabra actual a la primera parte
            strncat(p1, m[i], strlen(m[i])); 
            // Agregar un espacio en blanco
            strncat(p1, " ", 1); 
        } else {
            #pragma omp critical
            // Agregar la palabra actual a la segunda parte
            strncat(p2, m[i], strlen(m[i])); 
            // Agregar un espacio en blanco para la impresion
            strncat(p2, " ", 1); 
        }
    }
    printf("Frase impar: %s\n", p1);
    printf("Frase par: %s\n", p2);

    return 0;
}
