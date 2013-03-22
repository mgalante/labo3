
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
	int fd_source;
	int fd_target;
	int read_size;
	int write_size;
	char buffer[1024];
	if(argc != 3)
	{
		printf("Debe ingresar 2 archivos");
		return EXIT_FAILURE;
	}


	pid_t pid  = fork();
	//Levanto el pid 

	switch(pid){
		case -1:
			perror("Al hacer el fork");
			break;
		case 0:
			printf("<HIJO> getpid: %d getppid: %d  pid(fork) %d \n", getpid(), getppid(), pid);
			fd_source = open(argv[2], O_RDONLY);
			if(fd_source == -1)
			{
				perror("Al abrir source");
				exit(EXIT_FAILURE);				
			}
			
			read_size = read(fd_source, buffer, 1023);
			printf("Lei %d\n",read_size );
			while(read_size >0)
			{ 
				printf("Lei Adentro %d\n",read_size );
				printf("Leyendo <hijo>\n");
				buffer[read_size] = '\0';
				printf("%s",buffer);
				read_size = read(fd_source, buffer, 1023);
			}
			printf("\n");
			close(fd_source);
			break;
		default:
			printf("<PADRE> getpid: %d getppid: %d  pid(fork) %d \n", getpid(), getppid(), pid);
			fd_source = open(argv[1], O_RDONLY);
			if(fd_source == -1)
			{
				perror("Al abrir source");
				exit(EXIT_FAILURE);				
			}
			
			fd_target = open("salida.txt", O_RDWR | O_TRUNC | O_CREAT, 0777);
			if(fd_target == -1)
			{
				perror("Al abrir destino");
				close(fd_source);
				exit(EXIT_FAILURE);				
			}

			while((read_size = read(fd_source, buffer, 1024)) >0)
			{
				write_size = write(fd_target,buffer,read_size);
				if(write_size != read_size)
				{
					break;
				}
			}

			close(fd_source);
			close(fd_target);

			if(read_size == -1)
			{
				perror("Error leyendo \n");
				exit(EXIT_FAILURE);		

			}
			else if(read_size > 0 && write_size == -1){
				perror("Error escribiendo \n");
				exit(EXIT_FAILURE);		
			}
			else if(read_size > 0 && write_size != read_size)
			{
				printf("No se pudo escribir todo el contenido del buffer \n");
				exit(EXIT_FAILURE);		
			}

	}
	return EXIT_SUCCESS;
}

