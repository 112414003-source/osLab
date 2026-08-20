#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
 // Name of the shared memory object
 const char *name = "/my_shm";
 // Size of the shared memory block (in bytes)
 const int SIZE = 4096;
 int shm_fd;
 void *ptr;
 /*
 1. Create the shared memory object
 O_CREAT: Create object if it doesn't exist
 O_RDWR: Open for reading and writing
 0666: Read/Write permissions for User, Group, and Others
 */
 shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
 if (shm_fd == -1) {
 perror("shm_open failed");
 return 1;
 }
 /* 2. Configure the size of the shared memory segment */
 if (ftruncate(shm_fd, SIZE) == -1) {
 perror("ftruncate failed");
 return 1;
 }
 /* 3. Map the shared memory object into memory */
 ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
 if (ptr == MAP_FAILED) {
 perror("mmap failed");
 return 1;
 }
 /* 4. Fork a child process */
 pid_t pid = fork();
 if (pid < 0) {
 perror("Fork failed");
 return 1;
 }
 else if (pid == 0) {
 /*
 CHILD PROCESS
 Reads the data from the shared memory segment
 */
 // Simple delay to ensure the parent writes first
 sleep(1);
 printf("\nChild: Read data from shared memory: \"%s\"\n", (char *)ptr);
 // Clean up memory mapping in child
 munmap(ptr, SIZE);
 close(shm_fd);
 }
 else {
 /*
 PARENT PROCESS
 Writes data into the shared memory segment
 */
 const char *message = "Hello from the Shared Memory!";
 
 // Copying data into the memory mapped region
 sprintf(ptr, "%s", message);
 printf("Parent: Wrote data to shared memory: \"%s\"\n", message);
 // Wait for child to finish reading before cleaning up resource
 wait(NULL);
 // Clean up and release shared memory resources
 munmap(ptr, SIZE);
 close(shm_fd);
 shm_unlink(name); // Deletes the shared memory segment from system
 }
 return 0;
}