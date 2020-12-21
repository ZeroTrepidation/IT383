#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(){

	char buffer[1000];

	printf("tummillo>");
	fgets(buffer, 150, stdin);

	strtok(buffer, "\n");

	char* commands[50];
	char* token = strtok(buffer, " ");
	token = strtok(NULL, " ");
	int len = 0;


	while (token != NULL){
		commands[len] = token;
		len++;
		token = strtok(NULL, " ");

	}

	char* arg_list[len+1];
	arg_list[len] = NULL;


	for(int i = len-1; i>=0; i--){
		arg_list[i] = commands[i];
	}

	char* program = arg_list[0];


	int pid = fork();

	printf("%d\n", pid);

	if(pid == -1) {
		//error occured
		printf("Error creating child");
	} else if (pid == 0) {
		printf("Child created");
		//child process
		if(execvp(arg_list[0], arg_list) == -1){
				printf("An error has occured");
				exit(0);
		}
	} else {
		wait(NULL);
		printf("Parent finished executing");
	}




}
