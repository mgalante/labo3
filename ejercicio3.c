
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

	printf("%d \n", (int)getpid());
	printf("%d \n", (int)getppid());

	if(argc != 3)
	{
		printf("debe llamarse con el nombre del archivo a crear y el texto");
		return EXIT_FAILURE;
	}
	
	/*int fd=creat(argv[1], 0777);
	if(fb == -1)
	{
		perror(" creando archivo");
		return EXIT_FAILURE;

	}*/

	int fd=open(argv[1], O_WRONLY|O_TRUNC|O_CREAT, 0777);
	if(fd == -1)
	{
		perror(" creando archivo");
		return EXIT_FAILURE;
	}
	write(fd,argv[2],strlen(argv[2]));
	close(fd);
	return EXIT_SUCCESS;
}