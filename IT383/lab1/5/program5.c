#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){

  //initialize variables
	char *filename = "./numbers.txt";
  int file;
  int j = 0;
  int n = 10;
  int intArray[n];

  //attempt to open file
  file = open(filename, O_CREAT | O_RDWR | O_TRUNC);
  if(file == -1){
    printf("Error opening the intended file\n" );
    exit(1);
  }

  /* Prompt user for input of 10 integers */
  while(j < 10){
    int num;
    printf("Enter integer %d: ", j+1);
    if (scanf("%d", &num) == 0) {
      printf("Please enter a valid integer\n");
      int t;
      while( (t=getchar()) != '\n' );
    }else{
      intArray[j] = num;
      j++;
    }
  }

  //print the output to the screen and store in file
  for(int i = 9; i >= 0; i--){
    char tempint = intArray[i];
    printf("p[%d] = %d\n",i ,intArray[i]);
    write(file, &tempint, sizeof(char));
  }

  close(file);
}
