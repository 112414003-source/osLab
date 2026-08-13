#include<stdio.h>
#include<signal.h>
#include<unistd.h>

/*
Signal handler function
This function executes whenever
the registered signal occurs.
*/
void handler(int signal_number)
{
printf("\nSignal received successfully\n");
printf("Signal Number : %d\n",
signal_number);
}

int main()
{

/*
Register SIGINT handler.
Normally SIGINT is generated
by pressing CTRL+C.
*/
signal(SIGINT, handler);

printf("Current Process ID: %d\n",
getpid());

printf("Generating SIGINT using raise()\n");

/*
raise() sends SIGINT signal
to the same process.
*/
raise(SIGINT);

printf("\nProgram execution completed\n");

return 0;
}