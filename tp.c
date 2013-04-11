#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int getFileList(int fd, const char* directory);
int sendFile(int fd, const char* directory, const char* filename);
int main()
{
    printf("Hello world!\n");
    
    creat("test_tp.txt", 0777);
	//fd file descriptor. -1 error.
	int fd = open("test_tp.txt", O_RDWR | O_TRUNC);    
    getFileList(fd,"./");

    sendFile(fd,"./","salida.txt");
    close(fd);

    return EXIT_SUCCESS;

}


int sendFile(int fd, const char* directory, const char* filename)
{
	char fullpath[1024];
	unsigned char buffer[1024];
	int read_size = 0;
	int write_size = 0;

	strcpy(fullpath,directory);
	strcat(fullpath, filename);

	int readfd = open(fullpath, O_RDONLY);
	if(readfd == 0){
		perror("Al leer archivo (104)");
		return 0;
	}

	lseek(readfd, 0, SEEK_SET);
		
	while((read_size = read(readfd, buffer, 1024)) > 0)
	{
		write_size = write(fd, buffer, read_size);
		if(write_size == -1)
		{
			perror("Al escribir en fd (105)");
			break;
		}
	}

	if(read_size < 0)
	{
		perror("Al leer archivo (106)");		
	}
	
	close(readfd);
	return 1;
}

int getFileList(int fd, const char* directory)
{

	struct dirent* direntry;
	struct stat statinfo;	    
 	DIR* dir;

 	dir = opendir(directory); //TODO recibirlo por argumento.

 	if(dir == NULL){
 		perror("Al abrir directorio (100)"); 		
 		return 0;
 	}

 	direntry = readdir(dir);
	if(direntry == NULL){
		perror("Al leer directorio (101)");
		closedir(dir);
		return 0;
	}

//statinfo = (struct stat*) malloc(sizeof(struct stat));
	char fullpath[1024];
	char buffer[1024];


	while(direntry != NULL){		
		if(strcmp(direntry->d_name, ".") != 0 &&  strcmp(direntry->d_name, "..") != 0)
		{
			strcpy(fullpath,directory);
			strcat(fullpath, direntry->d_name);

			if(stat(fullpath, &statinfo) == -1){
				perror("Al obtener informacion(103)");	
			}else{
				sprintf(buffer,"%s\t%lld\n\0" ,direntry->d_name,(long long) statinfo.st_size);
				write(fd, buffer, strlen(buffer));
			} 	
		}

		direntry = readdir(dir);			
	}
	
	sprintf(buffer, "\n\0");
	write(fd, buffer, strlen(buffer));

	closedir(dir);
//	free(statinfo);
	return 1;	
}