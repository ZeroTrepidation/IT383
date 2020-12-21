#ifndef STACK_H
#define STACK_H

struct stack{
  int count; //the number of integer values currently stored in the stack
  int *data; //this pointer will be initialized inside stack_init(). Also the actual size of the allocated memory will be determined by the "capacity" value that is given as one of the param in stack_init()
  int max; //the total number of integer values that can be stored in this stack
};

typedef struct stack stack_t;

void stack_init(stack_t *s, int capacity);
int stack_size(stack_t *s);
int stack_pop(stack_t *s);
void stack_push(stack_t *s, int e);
void stack_deallocate(stack_t *s);

#endif //STACK_H
