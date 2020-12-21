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
const int SIZE = 50000000;
const int BUFFER_SIZE = 1024;
const int NAME_SIZE = 20;
const int CONTENT_SIZE;
//name of the shared memory object
const char *name = "smtumm1_shm_filesharing";
//shared memory file descriptor
  int fd, destf;
//pointer to shared memoery object
  char filename[20];
  char buffer[BUFFER_SIZE];



  struct filesharing_struct {
    char flag;
    int size;
    char name[NAME_SIZE];
    char contents[CONTENT_SIZE];
  };

  struct filesharing_struct *ptr;

  //create shared memoery object
  fd = shm_open(name, O_RDONLY, 0666);

  if (fd < 0){
    printf("shm_open failed\n" );
    exit(-1);

  }

  //memory map the shared memory objecct
  ptr = (struct filesharing_struct *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);

  //read from the shared memory objecct
  if(ptr->flag == 'T'){

    int w;
    int size = ptr->size;
    int count = 0;

    printf("Enter the name of your destination file: " );
    fflush(stdin);
    fgets(filename, NAME_SIZE, stdin);
    strtok(filename, "\n");

    destf = open(filename, O_WRONLY | O_CREAT, S_IRWXU);
    if (destf == -1) {
      printf("Error accessing destination file 1\n" );
      exit(1);
    }

    printf("File is availible\n");
    printf("File size is %d bytes\n", ptr->size);
    printf("File name is: %s\n", ptr->name);

    do{
      if(size > 1024){
        w = 1024;
      } else {
        w = size;
      }

      for(int i=0; i<w; i++){
        buffer[i] = ptr->contents[i+count];
      }

      count+=w;
      write(destf, &buffer, w);
      size -= w;

    } while(w>0);

    printf("File downloaded successfully\n");
   }else{
    printf("There are no files availible.");
  }

  //remove the shared memory objecct
  shm_unlink(name);


  return 0;
}
