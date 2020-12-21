#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {

  if(argc == 4){

    const int BUFFER_SIZE = 1024;      //const for buffer size
    int srcf, destf1, destf2;   //initialize source files
    char buffer[BUFFER_SIZE];   //initialize buffer
    int r, w1, w2;              //initialize other ints

    //open source file
    srcf = open(argv[1], O_RDONLY);
    if(srcf == -1){
      printf("Error opening origin file\n");
    }

    //open destination file 1
    destf1 = open(argv[2], O_WRONLY | O_CREAT, S_IRWXU);
    if (destf1 == -1) {
      printf("Error accessing destination file 1\n" );
    }

    //open destination file 2
    destf2 = open(argv[3], O_WRONLY | O_CREAT, S_IRWXU);
    if (destf2 == -1) {
      printf("Error accessing destination file 2\n" );
    }

    //loop to read from src and copy to both file 1 and file 2
    do{
      r = read(srcf, &buffer, BUFFER_SIZE);
      w1 = write(destf1, &buffer, r);
      w2 = write(destf2, &buffer, r);
    } while((r > 0) && (w1 == r) && (w2 == r));\

    //check for successful EOF and no write errors
    if(r == 0 && w1 == 0 && w2 == 0){
        printf("Process completed.\n" );
        close(srcf);
        close(destf1);
        close(destf2);
    } else {
      printf("Error reading or writing file\n" );
      close(srcf);
      close(destf1);
      close(destf2);
    }



  }else{
    printf("Incorrect number of arguements!\n" );
  }

  return 0;
}
