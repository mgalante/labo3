
//a)Cuando un proceso recibe la senal sigusr1 este finaliza su ejecucion
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <signal.h>
 #include <dirent.h>
 #include <string.h>
#include <errno.h>


/*
int main(int argc, char* argv[]){

	int pid = getpid();
	
	while(1){
		printf("Vivo\n");
		sleep(1);
		kill(pid, SIGUSR1);
	}
	return EXIT_SUCCESS;
}
*/
//b)
/*
int terminar = 0;

void manejar_senal(int senal){
	printf("senal recibida");
	terminar = 1;
}

int main(int argc, char* argv[]){

	int pid = getpid();
	signal(SIGUSR1, manejar_senal);	
	
	while(1){
		printf("Vivo\n");
		sleep(1);
		kill(pid, SIGUSR1);
		if(terminar == 1){
			break;
		}
	}
	printf("Afuera del bucle");
	return EXIT_SUCCESS;
}

*/


//c)
/*
int main(int argc, char* argv[]){
	char directory[100];
	strcpy(directory,".");
	char file[100];
	strcpy(file,"tp.c");
	DIR *dir = opendir(directory);
	dirent *file_dirent;
	int encontrado = 0;

	
	while((file_dirent = readdir(dir)) != NULL){
		if(strcmp(file_dirent->d_name,file) == 0){
			encontrado = 1;
			break;
		}
	
	}

	if(encontrado == 1){
		printf("el archivo existe\n");
	}else{
		printf("el archivo no existe\n");
	}
	closedir(dir);
}

*/

//C) OTra version
/*
int main(int argc, char* argv[]){
	char file[100];
	strcpy(file,"tcacp.c");	
	struct stat buf;
	int ret = stat(file, &buf);

	if(errno == ENOENT){
		printf("el archivo no existe\n");
	}else{
		printf("el archivo existe\n");
	}

	printf("errno = %d\n",errno);
	printf("ENOENT = %d\n",ENOENT);
	perror(" HOLA");
}
*/