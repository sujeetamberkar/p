#include <stdio.h>
#include <mpi.h>
int main(int argc, char* argv[])
{
	// int arr[] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};
	int arr[] = {18, 523, 301};

	MPI_Init(&argc,&argv);
	int size, rank;

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank >= sizeof(arr)/sizeof(arr[0])) {
        MPI_Finalize();
    }

	int var = arr[rank];
	int answer = 0;
	while(var)
	{
		answer= answer* 10 +var%10;
		var=var/10;
	}
	arr[rank]=answer;
	MPI_Finalize();


	fprintf(stderr, "%d\t", arr[rank]);


	return 0;
}