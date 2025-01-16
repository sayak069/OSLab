#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>  
#include<sys/wait.h>    
#include<stdlib.h>  
int main() {
	int fd[2],nbytes;
	pid_t childpid;
	char string[80];
	char readbuffer[80];
	if (pipe(fd) == -1) {
        printf("Pipe failed");
        exit(1);
    }
	childpid=fork();
	if(childpid==-1) {
		printf("child process not created\n");
		exit(1);
	}
	else if(childpid==0) {
		close(fd[1]);
		nbytes=read(fd[0],readbuffer,sizeof(readbuffer));
		printf("inside child");
		if (nbytes == -1) {
            printf("Read failed");
            exit(1);
        }
		printf("\nreceived string: %s",readbuffer);
		int alpha=0,num=0,schar=0,i;
		for( i=0; readbuffer[i]!='\0'; i++) {
			if(isalpha(readbuffer[i]))
				alpha++;
			else if(isdigit(readbuffer[i]))
				num++;
			else if(!isspace(readbuffer[i]))
				schar++;
		}
		printf("\ntotal number of alphabets: %d",alpha);
		printf("\ntotal number of digits: %d",num);
		printf("\ntotal number of special characters: %d",schar);
		close(fd[0]);
		exit(0);
	}
	else{
		printf("inside parent\n");
		close(fd[0]);
		printf("enter a string: ");
		fgets(string, sizeof(string), stdin);
		if (string[strlen(string) - 1] == '\n') {
            string[strlen(string) - 1] = '\0';
        }   
		if (write(fd[1], string, strlen(string) + 1) == -1) {
            printf("Write failed");
            exit(1);
        }
        close(fd[1]);
        wait(NULL);
	}
	return 0;
}