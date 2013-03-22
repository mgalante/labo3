#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	//struct dirent *info;
	
	if(argc == 1)
	{
		printf("Debe ingresar un directorio \n");
		return EXIT_FAILURE;
	}

	DIR* dir = opendir(argv[1]); //TODO recibirlo por argumento.

	if(dir == NULL)
	{
		perror(" en el opendir");
		return EXIT_FAILURE;
	}		

	struct dirent* info = readdir(dir);
	//nombre, inodo, tipo de archivo (no sirve en tdas las distro), 
	//el rec length no es el tamano del archivo
	
	while(info != NULL){
		printf("%s \n", info->d_name);
		info = readdir(dir);
	}

	closedir(dir);
	return EXIT_SUCCESS;

}