#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

int main() 
{
	int n;
	printf("Enter the number of elements: ");
	scanf("%d", &n);
	int arr[n];
	printf("Enter %d elements: ", n);
	for (int i = 0; i < n; i++) 
	{
		scanf("%d", &arr[i]);
	}
	int searchElement;
	printf("Enter an element to search: ");
	scanf("%d", &searchElement);
	pid_t pid = fork();
	if (pid < 0) 
	{
		perror("Fork failed");
		return 1;
	}
	else if (pid == 0) 
	{
		int found = 0;
		for (int i = 0; i < n; i++) 
		{
			if (arr[i] == searchElement) 
			{
				found = 1;
				break;
			}
		}
		if (found) 
		{
			printf("Child: Element found in the array.\n");
		} 
		else 
		{
			printf("Child: Element not found in the array.\n");
		}
	} 
	else 
	{
		wait(NULL);
		printf("Parent: Child process completed.\n");
	}
	return 0;
}
