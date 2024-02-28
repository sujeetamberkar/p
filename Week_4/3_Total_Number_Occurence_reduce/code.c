#include <stdio.h>
#include <mpi.h>

#define ROWS 3  // Number of rows
#define COLS 3  // Number of columns

int main(int argc, char* argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Ensure there are exactly 3 processes running
    if (size != 3) {
        if (rank == 0) {
            printf("This program requires exactly 3 MPI processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    int matrix[ROWS][COLS];  // Matrix to be distributed
    int row[COLS];           // Buffer to receive a row
    int target;              // Target element to find
    int occurrences = 0;     // Occurrences of target in the row
    int totalOccurrences;    // Total occurrences of target across all rows

    // Initialize the matrix and input the target in the root process
    if (rank == 0) {
        printf("Root process initializing the matrix:\n");
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                matrix[i][j] = i * COLS + j;  // Example initialization
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
        printf("Enter the target element to find: ");
        scanf("%d", &target);
    }

    // Broadcast the target element to all processes
    MPI_Bcast(&target, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter the rows of the matrix to each process
    MPI_Scatter(matrix, COLS, MPI_INT, row, COLS, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process counts the occurrences of the target in its row
    for (int i = 0; i < COLS; i++) {
        if (row[i] == target) {
            occurrences++;
        }
    }

    // Reduce to find the total occurrences of the target across all processes
    MPI_Reduce(&occurrences, &totalOccurrences, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // The root process prints the total occurrences
    if (rank == 0) {
        printf("Total occurrences of %d: %d\n", target, totalOccurrences);
    }

    MPI_Finalize();
    return 0;
}
