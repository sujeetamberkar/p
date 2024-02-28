#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stdlib.h>

#define MAX_STRLEN 100
#define MAX_NUM_STRINGS 10

void reverseString(char * str)
{
	int n = strlen(str);
	for(int i = 0; i <n/2;i++)
	{
		char temp = str[i];
		str[i] = str[n-i-1];
		str[n-i-1]=temp;
	}

}
int main(int argc, char * argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	char input[MAX_STRLEN]= {0};
	char word[MAX_STRLEN]= {0};
	char words[MAX_NUM_STRINGS][MAX_STRLEN]; // 2 D array to store strings
	char wordsOutput[MAX_NUM_STRINGS][MAX_STRLEN]; // 2 D array to store strings


	if (rank==0)
	{
		printf("Enter a Sentence\n");
		fgets(input,sizeof(input),stdin);
		int num_of_words = 0;
		char *token = strtok(input," \t\n");
		while(token!=NULL && num_of_words<size)
		{
			strcpy(words[num_of_words],token);
			num_of_words++;
			token=strtok(NULL," \t\n");
		}
	}
	MPI_Scatter(words,MAX_STRLEN,MPI_CHAR,word,MAX_STRLEN,MPI_CHAR,0,MPI_COMM_WORLD);
	printf("\nRank %d has %s\n",rank,word);

	reverseString(word);

	MPI_Gather(word,MAX_STRLEN,MPI_CHAR,wordsOutput,MAX_STRLEN,MPI_CHAR,0,MPI_COMM_WORLD);

	if(rank == 0)
	{
		for(int i = 0; i <size;i++)
		{
			printf("%s\t",wordsOutput[i]);
		}
	}
	MPI_Finalize();
}