#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){

    int fd[2], fd2[2]; 
    if(pipe(fd) == -1){
        printf("\nAn error occurred while opening the pipe 1.");
        return 1;
    }
    if(pipe(fd2) == -1){
        printf("\nAn error occurred while opening the pipe 2.");
        return 1;
    }

    if(fork() > 0){ 
        close(fd[0]); 
        close(fd2[1]); 
        
        int arr[100], i, n;
        printf("\nEnter the size of an array: ");
        scanf("%d", &n);
        printf("Enter %d elements: ", n);
        for(i = 0; i < n; i++){
            scanf("%d", &arr[i]);
        }

        write(fd[1], &n, sizeof(int)); 
        if(write(fd[1], arr, sizeof(int) * n) == -1){
            printf("\nAn error occurred while writing.");
            return 2;
        }
        close(fd[1]); 
        

        int even_arr[100];
        int even_count;
        read(fd2[0], &even_count, sizeof(int)); 
        if(read(fd2[0], even_arr, sizeof(int) * even_count) == -1){
            printf("\nAn error occurred while reading.");
            return 3;
        }

        printf("\nEven Array: ");
        for(i = 0; i < even_count; i++){
            printf("%d ", even_arr[i]);
        }
        printf("\n");
        close(fd2[0]); 

    } else {  
        close(fd[1]);
        close(fd2[0]); 

        int n, i, j = 0;
        int a[100];
        int even_arr[100];

        read(fd[0], &n, sizeof(int)); 
        if(read(fd[0], a, sizeof(int) * n) == -1){
            printf("\nAn error occurred while reading.");
            return 3;
        }
        close(fd[0]); 

        for(i = 0; i < n; i++){
            if(a[i] % 2 == 0){
                even_arr[j] = a[i];
                j++;
            }
        }

        write(fd2[1], &j, sizeof(int)); 
        if(write(fd2[1], even_arr, sizeof(int) * j) == -1){
            printf("\nAn error occurred while writing.");
            return 2;
        }
        close(fd2[1]); 
    }

    return 0;
}
