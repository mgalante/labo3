#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



int main(int argc, char* argv[])
{


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
	struct dirent* info;
	struct stat* statinfo;	
	
	info = readdir(dir);


	statinfo = (struct stat*) malloc(sizeof(struct stat));

	//nombre, inodo, tipo de archivo (no sirve en tdas las distro), 
	//el rec length no es el tamano del archivo
	char fullpath[1024];


	while(info != NULL){		
		strcpy(fullpath,argv[1]);
		strcat(fullpath, info->d_name);


		if(stat(fullpath, statinfo) == -1)
			perror(" al obtener informacion");	
		else{

			printf("%lo \t %lld \t", (unsigned long) statinfo->st_mode, (long long) statinfo->st_size);
		} 	
		
		printf("%s \n", info->d_name);


		info = readdir(dir);			
	}


	closedir(dir);
	free(statinfo);

	return EXIT_SUCCESS;
}