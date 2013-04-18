#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *mi_funcion(void* arg);
int main(int argc, char* argv[])
{
	void* retval;
	pthread_t thid;
	printf("main principal \n");
	pthread_create(&thid, NULL, mi_funcion, NULL);
	printf("main principal luego del create %lu \n", thid);
	pthread_join(thid, &revtal);
	return EXIT_SUCCESS;
}

void *mi_funcion(void* arg)
{
	printf("Estoy en el trhead\n");
	return NULL;
}