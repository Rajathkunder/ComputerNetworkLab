#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

void bubbleSort(int arr[], int n) 
{
	for (int i = 0; i < n - 1; i++) 
	{
		for (int j = 0; j < n - i - 1; j++) 
		{
			if (arr[j] > arr[j + 1]) 
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

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
	pid_t pid = fork();
	if (pid < 0) 
	{
		perror("Fork failed");
		return 1;
	} 
	else if (pid == 0) 
	{
		bubbleSort(arr, n);
		printf("Child: Sorted array: ");
		for (int i = 0; i < n; i++) 
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
	} 
	else 
	{
		wait(NULL);
		printf("Parent: Child process completed.\n");
	}
	return 0;
}

