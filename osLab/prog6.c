#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
int main()
{
int fd[2];
pid_t pid;
char message[]="Hello from Parent Process";
char buffer[100];
/*
Create pipe
fd[0] -> Reading end
fd[1] -> Writing end
*/
if(pipe(fd)==-1)
{
printf("Pipe creation failed\n");
return 1;
}
/*
Create child process
*/
pid=fork();
if(pid < 0)
{
printf("Process creation failed\n");

return 1;
}
/*
Child Process:
Reads data from pipe
*/
else if(pid==0)
{
close(fd[1]);
// Child does not write
read(fd[0],buffer,sizeof(buffer));
printf("\nChild received message:\n");
printf("%s\n",buffer);
close(fd[0]);
}
/*
Parent Process:
Writes data into pipe
*/
else
{
close(fd[0]);
// Parent does not read
write(fd[1],message,strlen(message)+1);
printf("Parent sent message\n");
close(fd[1]);
}
return 0;
}