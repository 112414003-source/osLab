#include<stdio.h> 
#include<signal.h> 
#include<unistd.h>  
void handler(int signal_number) 
{ 
printf("\nSignal received successfully\n"); 
printf("Signal Number : %d\n", 
signal_number); 
} 
int main() 
{ 
signal(SIGINT, handler); 
printf("Current Process ID: %d\n", 
getpid()); 
printf("Generating SIGINT using raise()\n"); 
raise(SIGINT); 
printf("\nProgram execution completed\n"); 
return 0;
}