#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
//the size (in bytes) of shared memory object
const int SIZE = 4096;
//name of the shared memory object
const char *name = "smtumm1_shm_consumer_producer";
//strings written to shared memoory
const char *message_0 = "Hello";
const char *message_1 = "World!";

//shared memory file descriptor
int fd;
//pointer to shared memoery object
char *ptr;

  //create shared memoery object
  fd = shm_open(name, O_CREAT | O_RDWR, 0666);

  if (fd < 0){
    printf("shm_open failed\n" );
    exit(-1);

  }

  //configure the sze of the shared memoery object
  ftruncate(fd, SIZE);

  //memory map the shared memory objecct
  ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  //write to the shared memory objecct
  sprintf(ptr, "%s", message_0);
  ptr += strlen(message_0);
  sprintf(ptr, "%s", message_1);
  ptr += strlen(message_1);

}
