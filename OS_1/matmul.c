#include <stdio.h>
#include <pthread.h>

#define Max 3
#define Max_threads 9

int A[Max][Max];
int B[Max][Max];
int C[Max][Max];

typedef struct{
	int row;
	int col;
}ThreadData;

void* mul(void* arg){
	ThreadData* data = (ThreadData *)arg;
	int row = data->row;
	int col = data->col;
	C[row][col] = 0;
	for (int k = 0; k < Max; ++k)
	{
		C[row][col] += A[row][k] * B[k][col];
	}

	pthread_exit(0);

}


int main(int argc, char const *argv[])
{
	pthread_t threads[Max_threads];
	ThreadData thread_data[Max_threads];


	printf("Enter matrix A [3*3]: \n");
	for (int i = 0; i < Max; ++i)
	{
		for (int j = 0; j < Max; ++j)
		{
			scanf("%d", &A[i][j]);
		}
	}

	printf("Enter matrix B [3*3]: \n");
	for (int i = 0; i < Max; ++i)
	{
		for (int j = 0; j < Max; ++j)
		{
			scanf("%d", &B[i][j]);
		}
	}

	int thread_index = 0;
    for (int i = 0; i < Max; ++i) {
        for (int j = 0; j < Max; ++j) {
            thread_data[thread_index].row = i;
            thread_data[thread_index].col = j;
            pthread_create(&threads[thread_index], NULL, mul, (void*)&thread_data[thread_index]);
            thread_index++;
        }
    }

	for (int i = 0; i < Max_threads; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	printf("Matrix Multiplication is: \n");
	for (int i = 0; i < Max; ++i)
	{
		for (int j = 0; j < Max; ++j)
		{
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}

	return 0;
}