#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

int main(){
    int fd[2];
    int fd2[2];

    if(pipe(fd) == -1 || pipe(fd2) == -1){
        printf("\nAn error occurred while opening the pipes.");
        return 1;
    }

    int pid = fork();

    if(pid > 0){
        close(fd[0]);
        close(fd2[1]);

        int regno, m1, m2, m3;
        char grade[3];

        printf("\nEnter student Details:");
        printf("\nRegistration Number: ");
        scanf("%d", &regno);
        write(fd[1], &regno, sizeof(int));

        printf("\nMark 1: ");
        scanf("%d", &m1);
        write(fd[1], &m1, sizeof(int));

        printf("\nMark 2: ");
        scanf("%d", &m2);
        write(fd[1], &m2, sizeof(int));

        printf("\nMark 3: ");
        scanf("%d", &m3);
        write(fd[1], &m3, sizeof(int));

        close(fd[1]);

        read(fd2[0], grade, sizeof(grade));
        printf("\nGrade: %s\n", grade);

        close(fd2[0]);
    }
    else{
        close(fd[1]);
        close(fd2[0]);

        int regno, m1, m2, m3;
        float avg;
        char grade[3];

        read(fd[0], &regno, sizeof(int));
        read(fd[0], &m1, sizeof(int));
        read(fd[0], &m2, sizeof(int));
        read(fd[0], &m3, sizeof(int));

        avg = (m1 + m2 + m3) / 3.0;
        
        if(avg > 90)
            strcpy(grade, "A+");
        else if(avg > 80)
            strcpy(grade, "A");
        else if(avg > 70)
            strcpy(grade, "B");
        else if(avg > 60)
            strcpy(grade, "C");
        else if(avg > 50)
            strcpy(grade, "D");
        else if(avg > 40)
            strcpy(grade, "E");
        else
            strcpy(grade, "F-");

        write(fd2[1], grade, sizeof(grade));

        close(fd[0]);
        close(fd2[1]);
    }

    return 0;
}
