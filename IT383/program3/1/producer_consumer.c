#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

const int BUFFER_SIZE = 10;
int counter = 0;

void* producer(void* parameters) {
  int* buffer = (int*) parameters;
  int in = 0;
  int next_produced = 0;
  while (1){
    if(next_produced > 1000000){
      exit(0);
    } else {
      next_produced++;
    }
    while(counter == BUFFER_SIZE);

    buffer[in] = next_produced;
    in = (in + 1) % BUFFER_SIZE;
    counter++;
  }
}

void* consumer(void* parameters) {
  int* buffer = (int*) parameters;
  int out = 0;
  int expected = 1;


  while (1) {
    while(counter == 0);

    int next_consumed = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    counter--;

    if(next_consumed == expected){
      expected++;
    } else {
      printf("ERROR: The consumer recieved the sequence up to %d correctly. The next number (incorrect) was %d\n", expected-1, next_consumed);
      exit(1);
    }

  }
  exit(0);
}


int main() {

  int buffer[BUFFER_SIZE];

  pthread_t producerid;
  pthread_t consumerid;

  pthread_create(&producerid, NULL, &producer, &buffer);
  pthread_create(&consumerid, NULL, &consumer, &buffer);

  pthread_join(producerid, NULL);
  pthread_join(consumerid, NULL);

  return 0;
}
