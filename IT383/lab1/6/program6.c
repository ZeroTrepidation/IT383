#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  //initialize variables
  char filename[50];
  FILE *file;

  //prompt user
  printf("Enter a filename: ");
  scanf("%s", filename);

  //attempt to open file
  file = fopen (filename,"r");

  //if file successfull opened
  if (file!=NULL) {

    //iniitialize required variables
    int lineCount = 0, wordCount = 0;
    int n=100;
    char line[100];

    //while there are still lines to read
    while( fgets(line, n, file) != NULL){

      //iniitialize required variables
      char *token;

      //increment the line count and then tokenize the line
      lineCount++;
      token = strtok(line, " ");

      //while there are still tokens i.e. words
      while (token != NULL) {

        //increment word counter and go to next word
        wordCount++;
        token = strtok(NULL, " ");
      }

    }
	
    fclose(file);	

    //output line and wordcount
    printf("The line count is: %d\nThe word count is: %d\n", lineCount, wordCount );

  //else will execute if the file is not found
  }else{
    printf("File does not exist\n");
    exit(1);
  }

  return 0;
}
