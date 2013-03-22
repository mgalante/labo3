//4) Listar todos los archivos de un directorio y listar recursivamente todos los archivos y
//directorios interiores junto con el tamaño de cada uno.
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


//1) Listar todos los archivos y directorios de un directorio pasado por parámetro.
// 2) Listar todos los archivos pasados de un directorio pasado por parámetro y escribir por pantalla la cantidad de bytes que ocupan en total.

int main(int argc, char* argv[])
{
	DIR* dir;
	struct dirent* dir_info;
	struct stat* stat_info;	
	char fullpath[1024];
	long long totalsize = 0;

	if(argc == 1)
	{
		printf("Debe ingresar un directorio \n");
		return EXIT_FAILURE;
	}

	dir = opendir(argv[1]); 

	if(dir == NULL)
	{
		perror(" en el opendir");
		return EXIT_FAILURE;
	}

	stat_info = (struct stat*) malloc(sizeof(struct stat));

	dir_info = readdir(dir);


	while(dir_info != NULL)
	{
		strcpy(fullpath, argv[1]);
		strcat(fullpath, dir_info->d_name);
		

		if(stat(fullpath, stat_info) == -1)
		{
			perror(" leyendo stat");
		}
		else
		{
			printf("%lo \t %lld \t %s\n", (unsigned long) stat_info->st_mode, (long long) stat_info->st_size, dir_info->d_name);
			totalsize += (long long) stat_info->st_size;
		}
		dir_info = readdir(dir);
	}
	printf("TOTAL: %lld\n", totalsize);
	
	closedir(dir);
	return EXIT_SUCCESS;
}

void listar_archivos(char *fullpath)
{

	DIR* dir;
	struct dirent* dir_info;
	struct stat* stat_info;	
	char fullpath[1024];
	long long totalsize = 0;

	dir = opendir(fullpath); 

	if(dir == NULL)
	{
		perror(" en el opendir");
		return EXIT_FAILURE;
	}

	stat_info = (struct stat*) malloc(sizeof(struct stat));

	dir_info = readdir(dir);


	while(dir_info != NULL)
	{
		strcpy(fullpath, argv[1]);
		strcat(fullpath, dir_info->d_name);
		

		if(stat(fullpath, stat_info) == -1)
		{
			perror(" leyendo stat");
		}
		else
		{
			printf("%lo \t %lld \t %s\n", (unsigned long) stat_info->st_mode, (long long) stat_info->st_size, dir_info->d_name);
			totalsize += (long long) stat_info->st_size;
			if(S_
		}
		dir_info = readdir(dir);
	}
	printf("TOTAL: %lld\n", totalsize);
	
	closedir(dir);	
}