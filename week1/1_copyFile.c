
//Write a program to copy one file to another using file system calls.

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

void main()
{
	char buffer;
	int file1, file2;
	file1 = open("first_file.txt",O_RDONLY);
	if(file1 == -1)
	{
		printf("error opening first_file\n");
		close(file1);
		return;
	}
	file2=open("second_file",O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	while(read(file1,&buffer,1))
	{
		write(file2,&buffer,1);
	}
	printf("successfully copied to second file");
	close(file1);
	close(file2);
}






