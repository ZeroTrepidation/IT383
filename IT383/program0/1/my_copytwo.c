#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

  if(argc == 4){

    const int BUFFER_SIZE = 1024;

    FILE *SRCFILE, *DESTFILE1, *DESTFILE2;

    SRCFILE = fopen(argv[1], "r");
  	if (SRCFILE == NULL) {
  		fprintf(stderr, "File %s could not be opened\n", argv[1]);
  		exit(1);
  	}

    DESTFILE1 = fopen(argv[2], "w");
  	if (DESTFILE1 == NULL) {
  		fprintf(stderr, "File %s could not be opened\n", argv[2]);
  		exit(1);
  	}

    DESTFILE2 = fopen(argv[3], "w");
  	if (DESTFILE2 == NULL) {
  		fprintf(stderr, "File %s could not be opened\n", argv[3]);
  		exit(1);
  	}

    size_t r, w1, w2;
    char buffer[BUFFER_SIZE];


    do{
      r = fread(buffer, sizeof(char), BUFFER_SIZE, SRCFILE);
      w1 = fwrite(buffer, sizeof(char), r, DESTFILE1);
      w2 = fwrite(buffer, sizeof(char), r, DESTFILE2);

    } while((r > 0) && (r == w1) && (r == w2));
    if(feof(SRCFILE)){
      fclose(SRCFILE);
      fclose(DESTFILE1);
      fclose(DESTFILE2);
    }else{
      printf("There was an error writing to the files!\n" );
      fclose(SRCFILE);
      fclose(DESTFILE1);
      fclose(DESTFILE2);
    }

  }else{
    printf("Wrong number of arguements\n");
  }

  return 0;
}
