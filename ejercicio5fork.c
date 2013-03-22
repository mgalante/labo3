#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	//int m=atoi(argv[1]);
	int m = 5;
	int i = 0;
	int p_pid = getpid();

	for(i=0;i<m;i++)
	{
		
		int pid = fork();

		if(pid == 0)
		{		
			printf("current %d padre %d \n", getpid(), getppid());			
		}
		else if(pid == -1)
		{

			perror("");
			exit(EXIT_FAILURE);
		}
		else
		{
			//printf("hijo %d current %d padre %d \n", pid, getpid(), getppid());
			//sleep(10);
			wait(NULL);
			exit(EXIT_SUCCESS);
		}
	}
/*
	if(p_pid == getpid())
		for(i=0;i<m;i++)
			wait();
*/

	return EXIT_SUCCESS;
}