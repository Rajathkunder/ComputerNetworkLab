// Write a program to demonstrate the concept of parent & child processes using fork () system call in which the parent reads a file name from the keyboard and child process uses the file name and reads first 10 characters from the file.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
	char filename[100];
	printf("Enter a filename: ");
	scanf("%s", filename);
	pid_t pid = fork();
	if (pid < 0) 
	{
		perror("Fork failed");
		return 1;
	}
	else if (pid == 0) 
	{
		FILE *file = fopen(filename, "r");
		if (file == NULL) 
		{
			perror("Error opening file");
			return 1;
		}
		char content[11];
		fread(content, sizeof(char), 10, file);
		content[10] = '\0';
		printf("Child: First 10 characters from the file: %s\n", content);
		fclose(file);
	} 
	else 
	{
		wait(NULL);
		printf("Parent: Child process completed.\n");
	}
	return 0;
}

 











 

