#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

const int BUFFER_SIZE = 20;
const int THREAD_COUNT = 2;

struct sort_param {
  int low;
  int high;
  int *arr;
};

void swap(int* a, int* b){
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++){
    if (arr[j] < pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}

int quicksort(int arr[], int low, int high) {
  if (low < high){
    int pi = partition(arr, low, high);

    quicksort(arr, low, pi - 1);
    quicksort(arr, pi + 1, high);
  }
}
//
// void threadArrInitialize(int numArr[], int size){
//
//   pthread_t threadArr[THREAD_COUNT];
//   int highArr[THREAD_COUNT];
//   int lowArr[THREAD_COUNT];
//   int temp = size / THREAD_COUNT;
//   int currentIndex = size;
//
//   for (size_t i = THREAD_COUNT - 1; i >= 0; i--) {
//     highArr[i] = currentIndex;
//     currentIndex -= temp;
//     if(i == 0){
//       lowArr[i] = 0;
//     } else {
//       lowArr[i] = currentIndex
//       currentIndex -= 1;
//     }
//   }
//
//
void* parallelSort(void* parameters) {
  struct sort_param* p = (struct sort_param*) parameters;
  quicksort(p->arr, p->low, p->high);
}

// void parallelSort(int threadArr, int lowArr, int highArr, int numArr) {
//
// }

int main(int argc, char const *argv[]) {

  if (argc == 2) {

    int fd;
    char* buffer = (char*)malloc(sizeof(char)*BUFFER_SIZE);
    int* numArr;
    int* sortedArr;
    FILE *file;

    file = fopen(argv[1], "r");

    fgets(buffer, sizeof(char)*BUFFER_SIZE, file);
    // char* temp = strtok(buffer, "#");
    // printf("%s\n", temp );

    int size = atoi(strtok(buffer, "#"));
    if (size == 0) {
      printf("Error parsing or 0 numbers to read\n" );
      exit(1);
    }

    numArr = (int*)malloc(sizeof(int)*size);
    int count = 0;

    while (fgets(buffer, BUFFER_SIZE, file) != NULL){
      if(count<size){
        numArr[count] = atoi(buffer);
        count++;
      } else {
        printf("Not enough space in array.\n" );
      }

    }

    // quicksort(numArr, 0, size);
    //


    pthread_t threadArr[THREAD_COUNT];
    struct sort_param tp[THREAD_COUNT];
    int temp = size / THREAD_COUNT;
    int currentIndex = size;


    for (int i = THREAD_COUNT - 1; i >= 0; i--) {
      tp[i].arr = numArr;
      tp[i].high = currentIndex;
      currentIndex -= temp;
      if(i == 0){
        tp[i].low = 0;
      } else {
        tp[i].low = currentIndex;
        currentIndex -= 1;
      }
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
      pthread_create (&threadArr[i], NULL, &parallelSort, &tp[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
      pthread_join(threadArr[i], NULL);
    }


    sortedArr = (int*)malloc(sizeof(int) * size);

    int i = 0;
    while(i < size){
      int tLow;
      int tHigh;
      int lowestInt = numArr[tp[0].low];
      int currLowInd = 0;

      for(int j; j < THREAD_COUNT; j++){
        tLow = tp[j].low;
        tHigh = tp[j].high;
        if(numArr[tLow] < lowestInt && tLow <= tHigh){
          currLowInd = j;
          lowestInt = numArr[tLow];
          printf("lowest index is %d", tLow)
        }

      }

      tp[currLowInd].low = tp[currLowInd].low + 1;

      sortedArr[i] = lowestInt;
      i++;
    }


    for (size_t i = 0; i < size; i++) {
      printf("%d\n", sortedArr[i] );
    }



  } else if(argc == 1) {
    printf("Too few arguments!\n");
  } else {
    printf("Too many arguments!\n");
  }


  return 0;
}
