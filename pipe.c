#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>  //for read() and write()
#include<sys/wait.h>    //for wait()
#include<stdlib.h>  //for exit()
int main() {
	int fd[2];
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
		printf("inside child");
		close(fd[1]);

		if (read(fd[0],readbuffer,sizeof(readbuffer)) == -1) {
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




/*
Explanation of the program
---------------------------
1. Pipe Creation:
The pipe(fd) system call is used to create a unidirectional data channel:

    fd[0]: Used for reading.
    fd[1]: Used for writing.
If pipe(fd) fails, the program exits with an error message.

2. Process Creation:
The fork() system call creates a child process:
    If fork() returns -1, the child process could not be created, and the program exits with an error message.
    If fork() returns 0, the process is the child process.
    If fork() returns a positive value, it is the parent process.

3. Parent Process:
    The parent process prompts the user to enter a string.
    It writes the input string to the write-end of the pipe (fd[1]) and then closes it.
    It waits for the child process to finish using wait(NULL).

3.Child Process:
    The child process reads the string from the read-end of the pipe (fd[0]).
    It analyzes the string to count:
        Alphabets using isalpha().
        Digits using isdigit().
        Special characters by checking if the character is not a space and not alphanumeric.
    It prints the counts for each category.
    The read-end of the pipe is then closed, and the child process exits.

Notes:
1. Edge Case Handling:
    Ensure the input string size is within the bounds of the buffer.
    The program removes the trailing newline character using fgets and strlen check.

2. Error Handling:
    Handles potential failures of pipe, fork, read, and write.

3. Synchronization:
    The parent waits for the child to complete using wait(NULL) to avoid orphan processes.
*/
