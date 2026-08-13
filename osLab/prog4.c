#include <stdio.h>
#include <unistd.h> // fork(), getpid(), getppid()
#include <fcntl.h>

int main()
{
pid_t pid; // Variable to store process ID returned by fork()

printf("Program execution started\n");

/*
fork() creates a new process.
Return value:
> 0 : Executing in parent process (value is child PID)
= 0 : Executing in child process
< 0 : Process creation failed
*/
pid = fork();

// Check whether process creation failed
if(pid < 0)
{
printf("Unable to create child process\n");
return 1;
}

/*
Child process block
pid value will be 0 inside child process.
*/
else if(pid == 0)
{
printf("\n--- Child Process ---\n");
// Display child's own process ID
printf("Child Process ID : %d\n", getpid());

// Display parent's process ID
printf("Parent Process ID : %d\n", getppid());
}

/*
Parent process block
pid contains the child process ID.
*/
else
{
printf("\n--- Parent Process ---\n");

// Display parent's own process ID
printf("Parent Process ID : %d\n", getpid());

// Display child process ID
printf("Child Process ID : %d\n", pid);
}

printf("\nProcess execution completed\n");

return 0;
}