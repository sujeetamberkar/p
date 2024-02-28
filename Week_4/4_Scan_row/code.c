#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4 // Matrix size is 4x4

void printMatrix(int matrix[N][N], int rank);

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4) {
        if (rank == 0) {
            printf("This program requires exactly 4 MPI processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    int matrix[N][N] = {
        {1, 2, 3, 4},
        {1, 2, 3, 1},
        {1, 1, 1, 1},
        {2, 1, 2, 1}
    };

    int row[N]; // Buffer for each process to store its row
    int resultRow[N]; // Result row after MPI_Scan

    // Distribute rows of the matrix to each process
    MPI_Scatter(matrix, N, MPI_INT, row, N, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform an inclusive scan on each row
    MPI_Scan(row, resultRow, N, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // Gather the results back to the root process
    MPI_Gather(resultRow, N, MPI_INT, matrix, N, MPI_INT, 0, MPI_COMM_WORLD);

    // Only the root process prints the final matrix
    if (rank == 0) {
        printf("Output:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}

