#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main (int argc, char * argv[])
{
	int rank, size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	char strv[]= "HelLo";

	if(rank > strlen(strv))
	{
		fprintf(stderr, "Out of Bound\n");
	}

	if(strv[rank]>='A' && strv[rank]<='Z')
	{
		strv[rank]=strv[rank] + 32;
	}
	else if (strv[rank]>='a' && strv[rank]<='z')
	{
		strv[rank] = strv[rank] - 32;
	}


	fprintf(stdout,"%s\n",strv);
	MPI_Finalize();



}
