
//13)
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <fcntl.h>
  #include <stdio.h>
  #include <errno.h>
  #include <unistd.h>
  #include <string.h>
  #include <stdlib.h>
  #include <sys/ipc.h>
  #include <sys/sem.h>


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

void print_ej(int semid,int thissem,int othersem)
{
	int count = 3;
	while(count > 0)
	{
		cwait(semid, thissem);
		count--;
		if(thissem == 0)
		{
			printf("0\n");

		}
		else
		{
			printf("1\n");
		}
		csignal(semid,othersem);
	}
}

int main(int argc, char* argv[])
{
	int error;
	int semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0777);
	
	if(semid == -1)
		perror("al abrir semaforo");
	
	error = semctl(semid, 0, SETVAL, 1);
	
	if(error == -1)
		perror(" al inicializar 0");
	
	error = semctl(semid, 1, SETVAL, 0);
	
	if(error == -1)
		perror(" al inicializar 1");
	
	pid_t pid  = fork();
	pid  = fork();

	int thissem, othersem;
	int count = 3;
	//Levanto el pid 

	switch(pid){
		case (-1):
			perror("");
			break;
		case (0):
			print_ej(semid,0,1);
			break;
		default:
			print_ej(semid,1,0);
//			printf("<PADRE> getpid: %d getppid: %d  pid(fork) %d \n", (int)getpid(), getppid(), pid);
			break;
	}

	


	//Levanto el ppid del padre
	//printf("%d \n", (int)getppid());

	return EXIT_SUCCESS;
}

