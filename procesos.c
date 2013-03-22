
//3) Crear un programa que cree un archivo pasado por parámetro y le colque como contenido el
//segundo parámetro. Ejemplo, si se ejecuta a.out hola.txt “este es el contenido” deberá crear un
//archivo hola.txt con el contenido “este es el contenido”.
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <fcntl.h>
  #include <stdio.h>
  #include <errno.h>
  #include <unistd.h>
  #include <string.h>
  #include <stdlib.h>

int main(int argc, char* argv[])
{

	pid_t pid  = fork();
	//Levanto el pid 

	switch(pid){
		case (-1):
			perror("");
			break;
		case (0):
			printf("<HIJO> getpid: %d getppid: %d  pid(fork) %d \n", (int)getpid(), getppid(), pid);
			break;
		default:
			printf("<PADRE> getpid: %d getppid: %d  pid(fork) %d \n", (int)getpid(), getppid(), pid);
			break;
	}

	//Levanto el ppid del padre
	//printf("%d \n", (int)getppid());

	return EXIT_SUCCESS;
}