#include <stdio.h>
#include <mpi.h>
#include <string.h>

// Function to toggle case of a string
char* toggleString(char a[], int len) {
    for (int i = 0; i < len; i++) {
        if (a[i] >= 'A' && a[i] <= 'Z')
            a[i] = a[i] + 32;
        else if (a[i] >= 'a' && a[i] <= 'z')
            a[i] = a[i] - 32;
    }
    return a;
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    char var[100]; // Buffer for input and output
    int len;

    if (rank == 0) {
        printf("Enter a Word: ");
        fflush(stdout); // Ensure prompt is printed before reading input
        fgets(var, sizeof(var), stdin); // Safer alternative to gets()
        len = strlen(var);

        MPI_Ssend(&len, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Ssend(var, len + 1, MPI_CHAR, 1, 1, MPI_COMM_WORLD);

        char ans[100]; // Buffer to receive toggled string
        MPI_Recv(ans, len + 1, MPI_CHAR, 1, 2, MPI_COMM_WORLD, &status);
        printf("The Received word is %s\n", ans);
    } else if (rank == 1) {
        MPI_Recv(&len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        char rec_var[100]; // Ensure buffer is large enough to receive
        MPI_Recv(rec_var, len + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
        char* answer = toggleString(rec_var, len);
        MPI_Ssend(answer, len + 1, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
