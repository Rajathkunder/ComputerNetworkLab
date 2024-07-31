#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s num1 num2 operator\n", argv[0]);
        return 1;
    }

    double num1 = atof(argv[1]);
    double num2 = atof(argv[2]);
    char operator = argv[3][0];

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        double result;
        switch (operator) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                if (num2 == 0) {
                    printf("Child: Division by zero not allowed.\n");
                    return 1;
                }
                result = num1 / num2;
                break;
            default:
                printf("Child: Invalid operator.\n");
                return 1;
        }
        printf("Child: Result: %lf\n", result);
    } else {
        // Parent process
        wait(NULL);
        printf("Parent: Child process completed.\n");
    }

    return 0;
}
