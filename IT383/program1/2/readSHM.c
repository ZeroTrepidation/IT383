#include <stdio.h>
#include <stdlib.h>
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
//shared memory file descriptor
int fd;
//pointer to shared memoery object
char *ptr;


  //create shared memoery object
  fd = shm_open(name, O_RDONLY, 0666);

  if (fd < 0){
    printf("shm_open failed\n" );
    exit(-1);

  }

  //memory map the shared memory objecct
  ptr = (char *)mmap(0, SIZE, PROT_READ , MAP_SHARED, fd, 0);

  //read from the shared memory objecct
  printf("%s", (char *)ptr);

  //remove the shared memory objecct
  shm_unlink(name);


  return 0;
}