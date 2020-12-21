#include <stdlib.h>
#include "dslib.h"


//iniitalizes the stack
void stack_init(stack_t *s, int capacity) {
  s->data = (int *)malloc(sizeof(int)*capacity);
  s->max = capacity;
  s->count = 0;
}

//returns the current size of the stack
int stack_size(stack_t *s) {
  return s->count;
}

//pops off the top of the stack
int stack_pop(stack_t *s) {
  if(s->count > 0){
    return s->data[--s->count];
  }else{
    return -9999;
  }

}

//pushes a given integer value onto the stack
void stack_push(stack_t *s, int e) {
  if(!(s->count>=s->max)){
    s->data[s->count] = e;
    s->count++;
  }
}

//deallocates the stack
void stack_deallocate(stack_t *s) {
  free(s->data);
  s->max = 0;
  s->count = 0;
}
