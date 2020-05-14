#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

int main(){
    int rank;
    int size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int MAX_NUMBERS = 100;
    int numbers[MAX_NUMBERS];
    int i = 0;
    for(i; i < MAX_NUMBERS; i++){
        numbers[i] = i;
    }
    int number_amount;
    
    if(rank == 0){
        srand(time(NULL));
        number_amount = (rand() / (float)RAND_MAX) * MAX_NUMBERS;
        MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("0 sent %d numbers to 1\n", number_amount);
        i = 0;
        for(i; i < number_amount; i++){
            printf("%d ", numbers[i]);
        }
        puts("");
    }else{
        MPI_Status status;
        MPI_Recv(numbers, MAX_NUMBERS, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &number_amount);
        printf("1 received %d numbers from 0. Message source = %d, tag = %d\n",
            number_amount, status.MPI_SOURCE, status.MPI_TAG);
        printf("0 sent %d numbers to 1\n", number_amount);
        i = 0;
        for(i; i < number_amount; i++){
            printf("%d ", numbers[i]);
        }
        puts("");
    }


    MPI_Finalize();
    return 0;
}
