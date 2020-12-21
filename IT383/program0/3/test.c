#include <stdio.h>
#include "dslib.h"


int main(int argc, char const *argv[]) {

  stack_t my_stack;
  int choice;
  int capacity;

  printf("Welcome to the Stack manager please enter a size for your stack: ");
  fflush(stdout);
  scanf("%d", &capacity);

  stack_init(&my_stack, capacity);

  printf("Your stack has been initialized with size: %d\n\n", capacity);
  fflush(stdout);

  do {

    int temp;

    printf("Stack management menu:\n"
            "Enter 1 to Push\n"
            "Enter 2 to Pop\n"
            "Enter 3 to Quit\n");
            fflush(stdout);
            scanf("%d", &choice);
            switch (choice) {
              case 1:
                printf("Enter the number you would like to push on the stack: ");
                scanf("%d", &temp);
                stack_push(&my_stack, temp);
                break;
              case 2:
                temp = stack_pop(&my_stack);
                if(temp!=-9999){
                  printf("The value %d has been popped from the stack\n", temp);
                }else{
                  printf("The stack is empty\n" );
                }
            }

  } while(choice!=3);

  stack_deallocate(&my_stack);


  return 0;
}
