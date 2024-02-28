#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int segment_length;
    char s1[100], s2[100], result[200]; // Assuming strings won't exceed 100 characters

    if (rank == 0) {
        // Root process reads the strings
        printf("Enter string S1: ");
        scanf("%s", s1);
        printf("Enter string S2: ");
        scanf("%s", s2);

        int length = strlen(s1); // Assuming S1 and S2 are of same length
        segment_length = length / size; // Length of each segment to be distributed
    }

    // Broadcast the segment length to all processes
    MPI_Bcast(&segment_length, 1, MPI_INT, 0, MPI_COMM_WORLD);

    char segment_s1[segment_length + 1]; // +1 for null terminator
    char segment_s2[segment_length + 1]; // +1 for null terminator
    char segment_result[segment_length * 2]; // Each character from S1 and S2 will be interleaved

    // Scatter segments of S1 and S2 to all processes
    MPI_Scatter(s1, segment_length, MPI_CHAR, segment_s1, segment_length, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(s2, segment_length, MPI_CHAR, segment_s2, segment_length, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Interleave characters from segment_s1 and segment_s2 into segment_result
    for (int i = 0, j = 0; i < segment_length; ++i) {
        segment_result[j] = segment_s1[i];
        j= j + 1;
        segment_result[j] = segment_s2[i];
        j = j+ 1;
    }

    // Gather the computed segments from all processes to the root
    MPI_Gather(segment_result, segment_length * 2, MPI_CHAR, result, segment_length * 2, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        result[segment_length * 2 * size] = '\0'; // Null terminate the final result
        printf("Resultant String: %s\n", result);
    }

    MPI_Finalize();
    return 0;
}
