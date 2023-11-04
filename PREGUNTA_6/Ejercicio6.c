#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        printf("Este programa debe ejecutarse con exactamente 2 procesos MPI.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        // Proceso 0 genera la Serie1
        int n = 2;
        int serie1[10000];
        serie1[0] = n;
        for (int i = 1; i < 10000; i++) {
            n += 2 * i + 1;
            serie1[i] = n;
        }
        // Envía Serie1 al Proceso 1
        MPI_Send(serie1, 10000, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        // Proceso 1 genera la Serie2
        int serie2[10000];
        int inicio = 2;
        int fin = 20000;
        int j = 0;

        for (int i = inicio; i <= fin; i += 2) {
            serie2[j] = i;
            j++;
        }

        // Recibe Serie1 del Proceso 0
        int serie1[10000];
        MPI_Recv(serie1, 10000, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Combina las series
        int resultado[20000];
        j = 0;

        for (int i = 0; i < 10000; i++) {
            resultado[j] = serie1[i];
            resultado[j + 1] = serie2[i];
            j += 2;
        }

        // Imprime el resultado
        for (int i = 0; i < 20000; i++) {
            printf("%d ", resultado[i]);
        }
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}
