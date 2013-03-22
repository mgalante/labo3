#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

	
	struct dirent* info;
	
	int i = 0;
	
	for(i=0;i<10;i++){

		info = readdir(dir);	
		while(info != NULL){
			if(strcmp("virus.exe", info->d_name) == 0)
			{
				printf("existe virus.exe\n");
			}
			info = readdir(dir);
		}

		rewinddir(dir);

	}

	closedir(dir);

	return EXIT_SUCCESS;

}