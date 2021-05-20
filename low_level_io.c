#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_BUFFER_SIZE (1<<16)
#ifndef STDOUT
#define STDOUT 1
#endif

int main(int argc, char **argv){
	if(argc==1){
		puts("Need a file name.");
		exit(1);
	}

	char file_name[100];
	int file_descriptor;
	//char buffer[MAX_BUFFER_SIZE];
	char *buffer;
	//char *buffer_tail;
	int read_size;
	int file_size;
	struct stat st_buffer;

	strcpy(file_name, argv[1]);	
	file_descriptor = open(file_name, O_RDONLY);
	if(file_descriptor < 0){
		printf("Open %s failed\n", file_name);
		exit(1);
	}

	fstat(file_descriptor, &st_buffer);
	file_size = st_buffer.st_size;
	//file_size = lseek(file_descriptor, 0, SEEK_END);
	//lseek(file_descriptor, 0, SEEK_SET);
	buffer = (char*)calloc(file_size+1, sizeof(char));
		fprintf(stderr, "file size:%d\n", file_size);

	//buffer_tail = buffer;
	/*
	while( (read_size = read(file_descriptor, buffer_tail, 4096)) > 0){
		buffer_tail += read_size;
		fprintf(stderr, "read_size:%d\n", read_size);
	}
	*/
		//*buffer_tail = '\0';
	read(file_descriptor, buffer, file_size);
	write(STDOUT, buffer, file_size);

	free(buffer);

	return 0;
}
