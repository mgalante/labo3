#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	int i = 0;
	while(i<argc)
	{
		printf("%d %s\n", i+1, argv[i]);
		i++;
	}
	return EXIT_SUCCESS;
}
