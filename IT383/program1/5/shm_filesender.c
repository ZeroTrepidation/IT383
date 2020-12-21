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
  const int CONTENT_SIZE = 30000000;
  //name of the shared memory object
  const char *name = "smtumm1_shm_filesharing";

  char filename[20];

  int fd;
  struct filesharing_struct *ptr;
  int srcf;


  //strings written to shared memoory
  struct filesharing_struct {
    char flag;
    int size;
    char name[NAME_SIZE];
    char contents[CONTENT_SIZE];
  };


  //open shared memory
  fd = shm_open(name, O_CREAT | O_RDWR, 0666);

  if (fd < 0){
    printf("shm_open failed\n" );
    exit(-1);

  }

  //truncate memory
  ftruncate(fd, SIZE);

  //map memory to struct
  ptr = (struct filesharing_struct *)mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

  //initialize flag
  ptr->flag = 'F';

  //allocate memory for contents
//  ptr->contents = (char *)malloc(sizeof(char)*CONTENT_SIZE);


   printf("Enter the name of the file you would like to send: " );
   fflush(stdin);
   fgets(filename, NAME_SIZE, stdin);
   strtok(filename, "\n");


  //open file to read from
  srcf = open(filename, O_RDONLY);
  if(srcf == -1){
    printf("Error opening origin file\n");
  }

  //initialize buffer and read integer
  int r, count = 0;
  char buffer[BUFFER_SIZE];

  //initialize size and name
  ptr->size = 0;
  sprintf(ptr->name, "%s", filename);

  //adjust pointer past header to file contents
  //ptr += 25;

  do{
    //read up to 1024 bytes from file
    r = read(srcf, &buffer, BUFFER_SIZE);
    //adjust flag
    if(ptr->flag == 'F') {
      ptr->flag = 'T';
    }
    //print to contents
    // sprintf(ptr->contents, "%s", buffer);
    for(int i = 0; i < r; i++){
      //printf("%c", buffer[0]);
      ptr->contents[count+i] = buffer[i];
    }
    count += r;
    ptr->size += r;
    printf("%s", buffer);
  }while(r > 0);


  printf("File uploaded successfully.\n");


  close(srcf);

}
