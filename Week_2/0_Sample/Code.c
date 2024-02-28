#include <mpi.h>
#include <stdio.h>
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

int main (int argc, char * argv[])
{
    int rank,size;
    int x;
    MPI_Init(&argc ,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Status status;
    if (rank==0)
    {
        fprintf(stderr, "Enter the values in the master process\t");
        scanf("%d",&x);
        MPI_Send(&x,1,MPI_INT,1,0,MPI_COMM_WORLD);
        fprintf(stderr,"\nI have send %d from process 0\n",x);
    }
    else {
        MPI_Recv(&x,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        fprintf(stderr,"I have recieved %d in process %d\n",x,rank);
    }
    MPI_Finalize();
    return 0;
}