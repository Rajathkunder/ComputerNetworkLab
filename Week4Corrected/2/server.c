#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>


struct msgbuf {
    long mtype;       
    float num[2];     
    char op;          
};

int main() {
    struct msgbuf buf;
    int msqid;
    int len = sizeof(buf) - sizeof(long); 
   
    msqid = msgget(1234, 0666);
    if (msqid < 0) {
        perror("msgget");
        exit(1);
    }

 
    msgrcv(msqid, &buf, len, 1, 0);

    float a = buf.num[0], b = buf.num[1], ans;
    char c = buf.op;


    switch (c) {
        case '+':
            ans = a + b;
            break;
        case '-':
            ans = a - b;
            break;
        case '*':
            ans = a * b;
            break;
        case '/':
            if (b != 0)
                ans = a / b;
            else {
                printf("Error: Division by zero\n");
                ans = 0;
            }
            break;
        default:
            printf("Invalid operator\n");
            exit(1);
    }

    buf.num[0] = ans; 
    buf.mtype = 2;    

    printf("%f %c %f = %f\n", a, c, b, ans);

  
    if (msgsnd(msqid, &buf, len, 0) >= 0) {
        printf("Result Sent to Client\n");
    } else {
        perror("msgsnd");
        exit(1);
    }

    return 0;
}
