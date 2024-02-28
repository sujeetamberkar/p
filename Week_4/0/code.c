#include <stdio.h>
#include <mpi.h>
# define BUFSIZE 100
void Error_Handler(int error_code)
{
	int error_class, length_of_error_string;
	char error_string [BUFSIZE];
	if (error_code != MPI_SUCCESS)
	{
		MPI_Error_class(error_code,&error_class);
		MPI_Error_string(error_code,error_string,&length_of_error_string);
		printf("[Error %d ]: %s ",error_class,error_string);
	}
}

int main (int argc, char *argv[])


{
	int rank,factsum,size;
	int fact = 1;
	MPI_Init(&argc,&argv);
// Correctly obtaining the rank and size
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Correct error handling after obtaining rank and size
    Error_Handler(MPI_Comm_rank(MPI_COMM_WORLD, &rank));
    Error_Handler(MPI_Comm_size(MPI_COMM_WORLD, &size));

	MPI_Comm_size(MPI_COMM_WORLD,&size);

	for(int i = 1; i <=rank;i++)
	{
		fact = fact * i;
	}

    int error = MPI_Reduce(&fact, &factsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if(rank==0)
		fprintf(stderr, "\n Sum of all factorial is %d",factsum);
	MPI_Finalize();
	return 0;

}