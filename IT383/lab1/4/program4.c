#include <stdio.h>
#include <stdlib.h>

int main(){

  FILE *file;
	char *filename = "./numbers.txt";

  int j = 0;
  int n = 10;
  int intArray[n];

	/*open the file for writing */
	file = fopen(filename, "w");
	if (file == NULL) {
		fprintf(stderr, "File %s could not be opened\n", filename);
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
    printf("p[%d] = %d\n",i ,intArray[i]);
    fprintf(file, "%c\n", intArray[i]);
  }

fclose(file);

}
