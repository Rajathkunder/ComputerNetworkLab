#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct msgbuf {
    long mtype;       
    float num[2];     
    char op;          
};

int main() {
    struct msgbuf buf;
    int msqid;
    int len = sizeof(buf) - sizeof(long); 

   
    msqid = msgget(1234, IPC_CREAT | 0777);
    if (msqid < 0) {
        perror("msgget");
        exit(1);
    }

    buf.mtype = 1; 

    
    printf("Enter two numbers:\n");
    scanf("%f", &buf.num[0]);
    scanf("%f", &buf.num[1]);
    printf("Enter operator (+, -, *, /):\n");
    scanf(" %c", &buf.op);

    
    if (msgsnd(msqid, &buf, len, 0) >= 0) {
        printf("Message Sent to Server\n");
    } else {
        perror("msgsnd");
        exit(1);
    }

   
    msgrcv(msqid, &buf, len, 2, 0);
    printf("Result: %f\n", buf.num[0]);

    
    msgctl(msqid, IPC_RMID, NULL);

    return 0;
}
