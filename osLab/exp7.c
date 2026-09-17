#include <stdio.h>              // for printf, sprintf, perror
#include <stdlib.h>              // for exit-related utilities (not heavily used here)
#include <string.h>              // for string handling (not directly used but common include)
#include <fcntl.h>               // for O_CREAT, O_RDWR flags used in shm_open
#include <sys/mman.h>            // for mmap, munmap, shm_open, shm_unlink, PROT_*, MAP_*
#include <sys/unistd.h>          // for fork, sleep, close
#include <sys/types.h>           // for pid_t type definition
#include <sys/wait.h>            // for wait()

int main() {
    const char *name = "/my_shm";   // name of the POSIX shared memory object (must start with '/')
    const int SIZE = 4096;          // size of the shared memory block in bytes (4 KB)

    int shm_fd;                     // file descriptor referring to the shared memory object
    void *ptr;                      // pointer that will point to the mapped memory region

    // Step 1: Create (or open) the shared memory object
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    // O_CREAT: create it if it doesn't already exist
    // O_RDWR: open it for both reading and writing
    // 0666: permissions (rw-rw-rw-) for owner/group/others

    if (shm_fd == -1) {             // check if shm_open failed
        perror("shm_open failed"); // print system error message
        return 1;                   // exit with failure code
    }

    // Step 2: Set the size of the shared memory segment
    if (ftruncate(shm_fd, SIZE) == -1) {
        // resizes the shared memory object to SIZE bytes
        perror("ftruncate failed");
        return 1;
    }

    // Step 3: Map the shared memory object into this process's address space
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    // 0: let the kernel choose the address
    // SIZE: number of bytes to map
    // PROT_READ | PROT_WRITE: memory can be read and written
    // MAP_SHARED: updates are visible to other processes mapping the same object
    // shm_fd: the file descriptor to map
    // 0: offset within the shared memory object

    if (ptr == MAP_FAILED) {        // check if mmap failed
        perror("mmap failed");
        return 1;
    }

    // Step 4: Fork a child process
    pid_t pid = fork();             // creates a new process; returns 0 in child, child's PID in parent

    if (pid < 0) {                  // fork failed
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // ---------- CHILD PROCESS BLOCK ----------
        sleep(1);                   // wait 1 second to let parent write first
        printf("\nChild: Read data from shared memory: \"%s\"\n", (char *)ptr);
        // read and print the string stored in shared memory

        munmap(ptr, SIZE);          // unmap the shared memory from child's address space
        close(shm_fd);              // close the child's file descriptor
    }
    else {
        // ---------- PARENT PROCESS BLOCK ----------
        const char *message = "Hello from the Shared Memory!";

        sprintf(ptr, "%s", message);
        // write the message string directly into the shared memory region

        printf("Parent: Wrote data to shared memory: \"%s\"\n", message);

        wait(NULL);                 // wait for the child process to finish before cleaning up

        munmap(ptr, SIZE);          // unmap the shared memory from parent's address space
        close(shm_fd);              // close the parent's file descriptor
        shm_unlink(name);           // remove the shared memory object from the system entirely
    }

    return 0;                       // end of program
}
