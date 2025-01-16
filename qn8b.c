#include <stdio.h>
#include <unistd.h>

int main() {
    int var = 10; // Initialize a variable
    printf("Original: Variable value = %d, Address = %p\n", var, (void*)&var);

    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } 
    else if (pid == 0) { // Child process
        printf("Child: Before modification: Value = %d, Address = %p\n", var, (void*)&var);
        var += 5; // Modify the variable
        printf("Child: After modification: Value = %d, Address = %p\n", var, (void*)&var);
    } 
    else { // Parent process
        printf("Parent: Before modification: Value = %d, Address = %p\n", var, (void*)&var);
        var -= 3; // Modify the variable
        printf("Parent: After modification: Value = %d, Address = %p\n", var, (void*)&var);
    }
    return 0;
}