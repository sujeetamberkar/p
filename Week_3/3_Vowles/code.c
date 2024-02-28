#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int n, send_count;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char stringvar[100] = {0}; // Initialize to zero to avoid garbage values.
    char stringtemp[25] = {0}; // Adjusted size based on division, ensure it's large enough.

    if (rank == 0)
    {
        fprintf(stderr, "Enter a String\t");
        fgets(stringvar, sizeof(stringvar), stdin);
        stringvar[strcspn(stringvar, "\n")] = 0; // Remove newline character if present.
        n = strlen(stringvar);
        printf("Size of the string is %d\n", n);
        send_count = (n + size - 1) / size; // Calculate the number of characters to send per process, rounding up.
        printf("\nPer process up to %d characters\n", send_count);
    }

    // Broadcast the send_count to all processes
    MPI_Bcast(&send_count, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Ensure the last process does not read beyond the string's end
    int remaining = n - (send_count * (size - 1));
    if (rank == size - 1 && remaining > 0) {
        send_count = remaining;
    }

    // Scatter the string among processes
    MPI_Scatter(stringvar, send_count, MPI_CHAR, stringtemp, send_count, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Null-terminate the received string segment
    stringtemp[send_count] = '\0';

    // Print the received string segment
    printf("\nRank = %d received: %s\n", rank, stringtemp);

    MPI_Finalize();
    return 0;
}
