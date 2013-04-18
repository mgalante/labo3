#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//CASO DE THREAD DETACHED
void *mi_funcion(void* arg);
int main(int argc, char* argv[])
{
	//void* retval;
	pthread_t thid;
	printf("main principal \n");
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thid, &attr, mi_funcion, NULL);

	printf("main principal luego del create %lu \n", thid);
	sleep(2);
	
	//pthread_join(thid, &revtal);
	
	return EXIT_SUCCESS;
}

void *mi_funcion(void* arg)
{
	printf("Estoy en el trhead\n");
	pthread_exit(NULL);
	return NULL;
}