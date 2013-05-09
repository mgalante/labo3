  #include <sys/types.h>
  #include <sys/stat.h>
  #include <sys/sem.h>
  #include <sys/ipc.h>
  #include <sys/shm.h>
  #include <string.h>
  #include <fcntl.h>
  #include <stdio.h>
  #include <errno.h>
  #include <unistd.h>
  #include <string.h>
  #include <stdlib.h>
  


void csignal(int semid, int sennum){	
	struct sembuf op;
	op.sem_op = 1;
	op.sem_num = sennum;
	op.sem_flg = 0;
	if(semop(semid,&op,1) == -1)
		perror("al usar csignal");
}


void cwait(int semid, int sennum){	
	struct sembuf op;
	op.sem_op = -1;
	op.sem_num = sennum;
	op.sem_flg = 0;
	if(semop(semid,&op,1) == -1)
		perror("al usar cwait");
}


int mainA(int argc, char* argv[])
{	
	//prefijo 1000 para semaforos y 2000 para shm
	key_t shmkey =   ftok(argv[0], 2001);
	int shmid = shmget(shmkey, sizeof(char) * 11, IPC_CREAT | 0777)	;
	char* text = (char*)shmat(shmid, NULL, 0);	
	strcpy(text,"ifcbdhajeg");

	key_t semkey =   ftok(argv[0], 1001);

	int semid = semget(semkey,3, IPC_CREAT | 0777);
	
	semctl(semid, 0, SETVAL, 1);
	semctl(semid, 1, SETVAL, 0);
	semctl(semid, 2, SETVAL, 0);

	do{
		cwait(semid, 0);
		//SECCION CRITICA ORDENAR!!~!
		printf("a\n");
		sleep(1);
		csignal(semid, 1);
	}while(1);
	return EXIT_SUCCESS;
}

int mainB(int argc, char* argv[])
{	
	key_t shmkey =   ftok(argv[0], 2001);
	int shmid = shmget(shmkey, 0, 0);
	char* text = (char*)shmat(shmid, NULL, 0);	
	
	key_t semkey =   ftok(argv[0], 1001);
	int semid = semget(semkey,0,0);
	
	do {
		cwait(semid, 1);
		//SECCION CRITICA
		printf("b\n");
		sleep(1);
		csignal(semid, 2);
	}while(1);
	return EXIT_SUCCESS;
}



int mainC(int argc, char* argv[])
{	
	
	key_t shmkey = ftok(argv[0], 2001);
	int shmid = shmget(shmkey, 0, 0);
	char* text = (char*)shmat(shmid, NULL, 0);	
	
	key_t semkey = ftotextk(argv[0], 1001);
	int semid = semget(semkey,0,0);

	do {
		cwait(semid, 2);
		//SECCION CRITICA
		printf("c\n");
		sleep(1);
		csignal(semid, 0);
	}while(1);

	shmdt(text);
	return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{		
	int semkey = atoi(argv[1]);
	int retval;
	switch(argv[1][0])
	{	
		case 'a':
			retval = mainA(argc, argv);
			break;
		case 'b':
			retval = mainB(argc, argv);
			break;
		case 'c':
			retval = mainC(argc, argv);
			break;
	}
	return retval;
}


/*  ->proc A
	cwait(sem_a);
    ORDEN
    csignal(sem_b);

	->proc B
	cwait(sem_b)
	ORDEN
    csignal(sem_c);

	->proc C
	cwait(sem_c)
	ORDEN
	cwait(sem_a) */