#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

pthread_mutex_t wrt;
pthread_mutex_t mutex;

int cnt = 1;
int numreader = 0;

void *writer(void *wno){
	pthread_mutex_lock(&wrt);
	cnt = cnt*2;
	printf("Writer %d modified count to %d\n",(*((int *)wno)),cnt);
	pthread_mutex_unlock(&wrt);

	return NULL;

}

void *reader(void *rno){
	pthread_mutex_lock(&mutex);
	numreader++;
	if(numreader == 1){
		pthread_mutex_lock(&wrt);
	}
	pthread_mutex_unlock(&mutex);

	printf("Reader %d: read count as %d\n",*((int *)rno),cnt);

	pthread_mutex_lock(&mutex);
	numreader--;
	if(numreader == 0){
		pthread_mutex_unlock(&wrt);
	}
	pthread_mutex_unlock(&mutex);

	return NULL;
}


int main(int argc, char const *argv[])
{
	
	pthread_t read[10], write[5];
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&wrt, NULL);

	int a[10] = {1,2,3,4,5,6,7,8,9,10}; 

	for (int i = 0; i < 10; ++i)
	{
		pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
	}

	for(int i = 0; i < 5; i++) {
    	pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
	}

	for(int i = 0; i < 10; i++) {
    	pthread_join(read[i], NULL);
	}
	for(int i = 0; i < 5; i++) {
    	pthread_join(write[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&wrt);

	return 0;
}