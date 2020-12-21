#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include "buffer.h"

buffer_item buffer[BUFFER_SIZE];
int counter, in, out, len;
pthread_mutex_t mutex;
sem_t full, empty;

const int ARR_LEN = 109585;
const int rAND_MAX = 10;

char** wordArr;

int insert_item(buffer_item item) {

  int retVal;

  sem_wait(&empty);
  pthread_mutex_lock(&mutex);

  if (counter < BUFFER_SIZE) {
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    counter++;
    retVal = 0;
  } else {
    retVal = -1;
  }

  pthread_mutex_unlock(&mutex);
  sem_post(&full);

  return retVal;
}

int remove_item(buffer_item *item) {
  int retVal;

  sem_wait(&full);
  pthread_mutex_lock(&mutex);

  if (counter > 0) {
    *item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    counter--;
    retVal = 0;
  } else {
    retVal = -1;
  }

  pthread_mutex_unlock(&mutex);
  sem_post(&empty);

  return retVal;
}

void* producer(void* parameters) {
  buffer_item item;



  while (1){
    sleep(rand() % rAND_MAX);

    int itemIndex = (rand() % len);
    item = wordArr[itemIndex];

    if(insert_item(item) == 0){
      printf("[Producer thread ID: %d] inserted an item (word: %s) into the buffer\n", (int)pthread_self(), item);
    } else {
      printf("Error inserting item\n" );
    }




  }
}

void* consumer(void* parameters) {
  buffer_item item;

  while (1) {
    sleep(rand() % rAND_MAX);



    if(remove_item(&item) == 0){
      printf("[Consumer thread ID: %d] removed an item (word: %s) from the buffer\n", (int)pthread_self(), item);
    } else {
      printf("Error consuming.\n");
    }

  }
  exit(0);
}


int main(int argc, char const *argv[]) {

  if (argc == 4) {

    int buffer[BUFFER_SIZE];
    FILE *file;
    len = 0;

    const long int runtime = strtol(argv[1], NULL, 0);
    const long int numProd = strtol(argv[2], NULL, 0);
    const long int numCons = strtol(argv[3], NULL, 0);

    wordArr = malloc(ARR_LEN * sizeof(char*));

    for (int i = 0; i < ARR_LEN; i++) {
      wordArr[i] = malloc(25 * sizeof(char));
    }

    file = fopen("wordsEn.txt", "r");


    while(fgets(wordArr[len], sizeof(char)*25, file) != NULL && len < ARR_LEN) {
      len++;
    }

    pthread_t producerArr[numProd];
    pthread_t consumerArr[numCons];

    counter = in = out = 0;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < numProd; i++) {
      pthread_create(&producerArr[i], NULL, &producer, NULL);
    }

    for (int i = 0; i < numCons; i++) {
      pthread_create(&consumerArr[i], NULL, &consumer, NULL);
    }




    sleep(runtime);

    return 0;
  } else {
    printf("Please enter exactly 3 arguements\n" );
    exit(1);
  }


}
