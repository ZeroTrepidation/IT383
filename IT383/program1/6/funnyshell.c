#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

/*  Function which checks for the < symbol
    Takes a list of arguements and size of list as paramaters
    Returns the location of the special character or -1 if not found*/
int redirectStdout(char** arg_list, int size){
  for(int i = 0; i < size; i++){
    if(arg_list[i][0] == '<') return i;
  }
  return -1;
}

/*  Function which checks for the > symbol
T   akes a list of arguements and size of list as paramaters
    Returns the location of the special character  or -1 if not found*/
int redirectStdin(char** arg_list, int size){
  for(int i = 0; i < size; i++){
    if(arg_list[i][0] == '>') return i;
  }
  return -1;
}

/*  Function which checks for the | symbol
    Takes a list of arguements and size of list as paramaters
    Returns the location of the special character or -1 if not found*/
int pipeChecker(char** arg_list, int size){
  for(int i = 0; i < size; i++){
    if(arg_list[i][0] == '|') return i;
  }
  return -1;
}

int parseReverseArray(char *buffer, char **arg_list){
  //strip the newline from the end of the buffer
  strtok(buffer, "\n");

  /*-----------Parsing section---------------*/
  /* This section is responsible for parsing
    the commands into an array and reversing
          the order of the arguements*/

  char *commands[50];

  char* token = strtok(buffer, " ");
  int arg_list_size = 0;


  while (token != NULL){
    commands[arg_list_size] = token;
    arg_list_size++;
    token = strtok(NULL, " ");

  }
  arg_list[arg_list_size] = NULL;

  int count = 0;

  for(int i = arg_list_size-1; i>=0; i--){
    arg_list[count] = commands[i];
    count++;
  }

  return arg_list_size;

  /*-----------Parsing section---------------*/
}

//Work in progress functions
// void execFg(char **arg_list) {
//
// }
//
// void execBg(char **arg_list) {
//
// }

int main(){

  const int BUFFER_SIZE = 1000;

  char buffer[BUFFER_SIZE];                                    //buffer array
  pid_t bg_process = 0;                                        //pid of the background process. 0 if doesnt exist


  //inital prompt message
  printf("Welcome to the Funny Shell created by Seth Tummillo. Type 'exit' to exit.\n" );

  do{

    // make sure the buffer is zeroed out
    bzero(buffer, BUFFER_SIZE);

    //clean up any running backgroun processes
    pid_t temp;
    while((temp = waitpid(-1, NULL, WNOHANG)) > 0) {
      printf("Done    pid: %d\n", temp);
      bg_process = 0;
    }

    //initial prompt and input from user
    printf("tummillo> ");
    fgets(buffer, 150, stdin);

    //if loop which will run if user enters something other than exit

    if((strcmp(buffer, "exit\n")) != 0 && buffer[0] != '\n'){

      char* arg_list[50];

      int arg_list_size = parseReverseArray(buffer, arg_list);

      int spChPos = 0;  //varible to store the location of the special character if one is encountered


      /* This series of if statements will look through the array
        of arguements and determine if any special operators exist
        within the array. These operations include redirection of
        stdout '<' and stdin '>', the pipe function '|', and
        the background operator '&' */

      if ((spChPos = redirectStdout(arg_list, arg_list_size)) >= 0) {


        if(spChPos == (arg_list_size - 1)){
          printf("No output destination specified\n");

        } else {





          int pid = fork();

      		if(pid == -1) {
      			//error occured
      			printf("Error creating child\n");
      		} else if (pid == 0) {

      			//child process
            int fd; //file descriptor
            char *filename = arg_list[spChPos + 1]; //destination file
            char *arg_list2[spChPos+1]; //updated arg_list


            for (int i = 0; i < spChPos; i++) {
              arg_list2[i] = arg_list[i];

            }
            arg_list2[spChPos] = NULL;

            if((fd = open(filename, O_CREAT | O_WRONLY, 0666)) < 0){
              printf("Error opening specified destination\n");
            }
            if(dup2(fd, 1) < 0) {
              printf("Error redirecting stdout\n" );
            }

      			if(execvp(arg_list2[0], arg_list2) == -1){
                printf("An error has occured\n");
                close(fd);
                exit(0);
            }


            close(fd);
      		} else {
      			wait(NULL);



      		}


        }



      } else if ((spChPos = redirectStdin(arg_list, arg_list_size)) >= 0) {

        //printf("contains > found at position: %d\n", spChPos);

        if(spChPos == (arg_list_size - 1)){
          printf("No input destination specified\n");

        } else {





          int pid = fork();

      		if(pid == -1) {
      			//error occured
      			printf("Error creating child\n");
      		} else if (pid == 0) {

      			//child process
            int fd; //file descriptor
            char *filename = arg_list[spChPos + 1]; //destination file
            char *arg_list2[spChPos+1]; //updated arg_list


            for (int i = 0; i < spChPos; i++) {
              arg_list2[i] = arg_list[i];
            }
            arg_list2[spChPos] = NULL;

            if((fd = open(filename, O_RDONLY, 0666)) < 0){
              printf("File does not exit\n");
            }
            if(dup2(fd, 0) < 0) {
              printf("Error redirecting stdin\n" );
            }

      			if(execvp(arg_list2[0], arg_list2) == -1){
                printf("An error has occured");
                close(fd);
                exit(0);
            }

            close(fd);
      		} else {
      			wait(NULL);

      		}

        }


      } else if ((spChPos = pipeChecker(arg_list, arg_list_size)) >= 0) {

        /* This section is responsible for splitting up the arguements before
        and after the pipe so that they can be called in seperate processes */

        int par_arg_size = arg_list_size - spChPos;
        int chld_arg_size = spChPos + 1;
        char *arg_list_parent[par_arg_size], *arg_list_child[chld_arg_size];

        for(int i = 0; i < par_arg_size-1; i++){
          arg_list_parent[i] = arg_list[spChPos+1];
        }
        arg_list_parent[par_arg_size - 1] = NULL;
        for(int i = 0; i < chld_arg_size-1; i++){
          arg_list_child[i] = arg_list[i];
        }
        arg_list_child[chld_arg_size-1] = NULL;


        int pid = fork();

    		if(pid == -1) {
    			//error occured
    			printf("Error creating child");
    		} else if (pid == 0) {

          int fd[2];
          pipe(fd);
          int pid = fork();

      		if(pid == -1) {
      			//error occured
      			printf("Error creating child");
      		} else if (pid == 0) {

            close(fd[0]);
            dup2(fd[1], 1);
      			if(execvp(arg_list_child[0], arg_list_child) == -1){
                printf("An error has occured");
                exit(0);
            }
      		} else {

            close(fd[1]);
      			dup2(fd[0], 0);
            if(execvp(arg_list_parent[0], arg_list_parent) == -1){
                printf("An error has occured");
                exit(0);
            }
      		}

    		} else {
    			wait(NULL);
    		}


      } else if (arg_list[arg_list_size-1][0] == '&') { //if statement checks if process should be created in background

        arg_list[arg_list_size-1] = NULL;


        if(bg_process == 0) {

          pid_t pid = fork();

          if(pid == -1) {
            //error occured
            printf("Error creating child");

          } else if (pid == 0) {


            if(execvp(arg_list[0], arg_list) == -1){
                printf("An error has occured");
                exit(0);
            }
            //child process

          } else {
            bg_process = pid;
            printf("Running (Pid: %d) &", pid);
            for(int i = arg_list_size-2; i >= 0; i--) {
              printf(" %s", arg_list[i]);
            }
            printf("\n");

          }

        } else {
          printf("Background process already running.\n");
        }



      } else if (strcmp(arg_list[0], "fg") == 0) {


        if(bg_process != 0){
          waitpid(bg_process, NULL, 0);
          bg_process = 0;
        } else {
          printf("No background processes exist\n");
        }


      } else {


        int pid = fork();

    		if(pid == -1) {
    			//error occured
    			printf("Error creating child");
    		} else if (pid == 0) {

    			//child process
    			if(execvp(arg_list[0], arg_list) == -1){
              printf("An error has occured");
              exit(0);
          }
    		} else {
    			wait(NULL);

    		}


      }



    }





  }while(strcmp(buffer, "exit\n") != 0);

}
