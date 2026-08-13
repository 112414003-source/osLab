#include <stdio.h>
#include <unistd.h> // fork(), getpid(), sleep()
#include <sys/wait.h> // wait()

int main()
{
pid_t pid;

/*
Create a child process
*/
pid = fork();

/*
Check process creation failure
*/
if(pid < 0)
{
printf("Process creation failed\n");
return 1;
}

/*
Child Process
pid == 0 indicates child execution.
*/
else if(pid == 0)
{
printf("\n--- Child Process Started ---\n");

printf("Child Process ID : %d\n", getpid());

// Simulate some processing time
sleep(3);

printf("Child Process Completed\n");
}

/*
Parent Process
Parent waits for child completion.
*/
else
{
printf("\n--- Parent Process Started ---\n");

printf("Parent is waiting for child process...\n");

/*
wait() suspends parent execution
until child process terminates.
*/

wait(NULL);

printf("Child process completed\n");
printf("Parent Process ID : %d\n", getpid());

printf("Parent Process Resumed\n");
}

return 0;
}