#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

int main() 
{
	FILE *file = fopen("file.txt", "w");
	if (file == NULL) 
	{
		printf("Error creating file");
		return 1;
	}
	fprintf(file, "Hello, this is the parent process writing to the file.\n");
	fclose(file);
	pid_t pid = fork();
	if (pid < 0) 
	{
		perror("Fork failed");
		return 1;
	} 
	else if (pid == 0) 
	{
		file = fopen("file.txt", "r");
		if (file == NULL) 
		{
			perror("Error opening file");
			return 1;
		}
		char buffer[100];
		while (fgets(buffer, sizeof(buffer), file) != NULL) 
		{
			printf("Child: %s", buffer);
		}
		fclose(file);
	} 
	else 
	{
		wait(NULL);
		printf("Parent: Child process completed.\n");
	}
	return 0;
}

