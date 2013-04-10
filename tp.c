#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main()
{
    printf("Hello world!\n");
    return 0;
}


int getFileList(int fd, char[] directory)
{

	struct dirent* info;
	struct stat* statinfo;	    
 	DIR* dir;

 	dir = opendir(directory); //TODO recibirlo por argumento.

 	if(dir == NULL){
 		perror("Al abrir directorio (100)"); 		
 		return 0;
 	}

 	info = readdir(dir);
	if(info == NULL){
		perror("Al leer directorio (101)");
		closedir(dir);
		return 0;
	}

	statinfo = (struct stat*) malloc(sizeof(struct stat));
	char fullpath[1024];
	strcpy(fullpath,directory);
	strcat(fullpath, info->d_name);


	return 1;	

}


void getFullPath(){

	while(info != NULL){		


		if(stat(fullpath, statinfo) == -1)
			perror(" al obtener informacion");	
		else{

			printf("%lo \t %lld \t", (unsigned long) statinfo->st_mode, (long long) statinfo->st_size);
		} 	
		
		printf("%s \n", info->d_name);


		info = readdir(dir);			
	}



}