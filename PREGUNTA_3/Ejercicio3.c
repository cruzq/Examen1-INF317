#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

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

    int i;
    for (i = rank; i < num; i += size) {
        if (i % 2 == 0) {
            // Agregar la palabra actual a la primera parte
            strncat(p1, m[i], strlen(m[i])); 
            // Agregar un espacio en blanco
            strncat(p1, " ", 1); 
        } else {
            // Agregar la palabra actual a la segunda parte
            strncat(p2, m[i], strlen(m[i])); 
            // Agregar un espacio en blanco para la impresion
            strncat(p2, " ", 1); 
        }
    }

    char p1_combined[100];
    char p2_combined[100];
    MPI_Reduce(p1, p1_combined, 100, MPI_CHAR, MPI_CHAR, MPI_CONCATENATE, 0, MPI_COMM_WORLD);
    MPI_Reduce(p2, p2_combined, 100, MPI_CHAR, MPI_CHAR, MPI_CONCATENATE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Frase impar: %s\n", p1_combined);
        printf("Frase par: %s\n", p2_combined);
    }

    MPI_Finalize();
    return 0;
}
