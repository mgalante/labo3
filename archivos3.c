#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char* argv[])
{
	//Lo crea si no existe.
	creat("texto.txt", 0777);
	//fd file descriptor. -1 error.
	int fd = open("texto.txt", O_RDWR | O_TRUNC);
	char buffer[1024];
	sprintf(buffer, "hola mundo"); //Le agrega un \0


	write(fd, buffer, strlen(buffer)); //el largo sin el \0

	int cant;
	char buffer2[1024];
	lseek(fd, 0, SEEK_SET);//mueve el puntero de lectura
	cant = read(fd, buffer2, 1024);
	printf("%d\n", cant);
	buffer2[cant] = '\0';
	printf("Lei %s \n", buffer2);
	close(fd); //IMPORTANTE para liberar recursos y bajar a disco.
	return 0;
}