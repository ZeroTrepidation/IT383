#include <pthread.h>
#include <stdio.h>
/* Prints x’s to stderr.
The parameter is unused.
Does not return.
*/
void* print_xs (void* unused)
{
  while (1)
    fputc ('x', stderr);
  return NULL;
  }
  /* The main program.
  */
int main ()
{
  pthread_t thread_id;

  pthread_create (&thread_id, NULL, &print_xs, NULL);

  while (1)
    fputc ('o', stderr);
  return 0;
}
