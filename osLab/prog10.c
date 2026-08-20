#include <stdio.h> // printf(), perror()
#include <stdlib.h> // exit()
#include <sys/stat.h> // stat(), struct stat
#include <unistd.h> // POSIX functions
#include <pwd.h> // getpwuid()
#include <grp.h> // getgrgid()
#include <time.h> // ctime()
int main() {
 // Variable to store file information
 struct stat fileStat;
 // Array to store the filename entered by the user
 char filename[100];
 // Read filename
 printf("Enter filename: ");
 scanf("%s", filename);
 // Get file information
 if (stat(filename, &fileStat) == -1) {
 perror("Error");
 return 1;
 }
 printf("\n===== File Information =====\n");
 // File size in bytes
 printf("File Size : %ld bytes\n", fileStat.st_size);
 // Inode number
 printf("Inode Number : %ld\n", fileStat.st_ino);
 // Number of hard links
 printf("Hard Links : %ld\n", fileStat.st_nlink);
 // User ID (Owner)
 printf("Owner UID : %d\n", fileStat.st_uid);
 // Group ID
 printf("Group GID : %d\n", fileStat.st_gid);
 // Owner name
 printf("Owner Name : %s\n", getpwuid(fileStat.st_uid)->pw_name);
 // Group name
 printf("Group Name : %s\n", getgrgid(fileStat.st_gid)->gr_name);
 // File permissions
 printf("\nPermissions : ");
 printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
 printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
 printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
 printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
 printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
 printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
 printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
 printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
 printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
 printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
 printf("\n");
 // Last access time
 printf("Last Access : %s", ctime(&fileStat.st_atime));
 // Last modification time
 printf("Last Modification : %s", ctime(&fileStat.st_mtime));
 // Last status change
 printf("Last Status Change : %s", ctime(&fileStat.st_ctime));
 return 0;
}