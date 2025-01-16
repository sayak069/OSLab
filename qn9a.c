#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int prime(int n){
    for(int i=2;i<=n/2;i++){
        if(n%i==0){
            return 0;
        }
    }
    return 1;
}
int main(){
    int fd[2],number,nbytes;
    pid_t childpid;
    if(pipe(fd)==-1){
        printf("pipe failed\n");
        exit(1);
    }
    childpid=fork();
    if(childpid==-1){
        printf("fork failed\n");
        exit(1);
    }
    else if(childpid==0){
        close(fd[1]);
        nbytes=read(fd[0],&number,sizeof(number));
        printf("inside child\n");
        if(nbytes==-1){
            printf("read failed\n");
            exit(1);
        }
        printf("value from parent: %d\n",number);
        if(prime(number)){
            printf("%d is prime\n",number);
        }
        else{
            printf("%d is not prime\n",number);
        }
        close(fd[0]);
        exit(0);
    }
    else{
        printf("inside parent\n");
        close(fd[0]);
        printf("enter a number: ");
        scanf("%d",&number);
        if(write(fd[1],&number,sizeof(number))==-1){
            printf("write failed\n");
            exit(1);
        }
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}