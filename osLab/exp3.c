#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <dirent.h> 
#include <string.h>
int main()
{
 int fd;
 char buffer[100];
 struct stat fileInfo;
 DIR *dir;
 struct dirent *entry;
 /*
 PART 1:
 Create and write data into a file using open() and write()
 */
 printf("\n--- Creating and Writing File ---\n");
 fd = open("student.txt", O_CREAT | O_WRONLY, 0644);
 if(fd < 0)
 {
 printf("File creation failed\n");
 return 1;
 }
 char data[] = "Linux System Calls Experiment\n"
            "B.Sc Cyber Security Laboratory";
 write(fd, data, strlen(data));
 close(fd);
 printf("Data written successfully\n");
 /*
 PART 2:
 Read file contents using open() and read()
 */
 printf("\n--- Reading File Content ---\n");
 fd = open("student.txt", O_RDONLY);
 if(fd < 0)
 {
 printf("File opening failed\n");
 return 1;
 }
 int bytes = read(fd, buffer, sizeof(buffer)-1);
 buffer[bytes] = '\0';
 printf("%s\n", buffer);
 close(fd);
 /*
 PART 3:
 Display file information using stat()
 */
 printf("\n--- File Information ---\n");
 if(stat("student.txt", &fileInfo) == 0)
 {
 printf("File Size : %ld bytes\n",
 fileInfo.st_size);
 printf("Number of Links: %ld\n",
 fileInfo.st_nlink);
 printf("Permissions : %o\n",
 fileInfo.st_mode & 0777);
 }
 else
 {
 printf("Unable to get file information\n");
 }
 /*
 PART 4:
 Create directory using mkdir()
 */
 printf("\n--- Creating Directory ---\n");
 if(mkdir("TestDirectory",0755)==0)
 {
 printf("Directory created successfully\n");
 }
 else
 {
 printf("Directory may already exist\n");
 }
 /*
 PART 5:
 Display directory contents using
 opendir() and readdir()
 */
 printf("\n--- Directory Contents ---\n");
 dir = opendir(".");
 if(dir == NULL)
 {
 printf("Cannot open directory\n");
 return 1;
 }
 while((entry = readdir(dir)) != NULL)
 {
 printf("%s\n", entry->d_name);
 }
 closedir(dir);
 printf("\nProgram completed successfully\n");
 return 0;
}
