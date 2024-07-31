#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

int main() {
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child: Multiplication table for %d:\n", num);
        for (int i = 1; i <= 10; i++) {
            printf("%d x %d = %d\n", num, i, num * i);
        }
    } else {
        // Parent process
        wait(NULL);
        printf("Parent: Child process completed.\n");
    }

    return 0;
}


