/*
  ECE 566 Parallel and Distributed Computing, Fall 2017
  Programming Project 2.
*/

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <random>
#include <sys/types.h>

#define NUM_THREADS  3

using namespace std;
pthread_mutex_t mutexsum;


double* fillArray(double* array, int nbElements) {
  //generate random numbers to fill the array
  int upper = 100; //max number allowed
  random_device rd; // obtain a random number from hardware
  mt19937 eng(rd()); // seed the generator
  uniform_real_distribution<> distr(0, 100);
  for (int i = 0; i < nbElements; i++) {
    array[i] = distr(eng);
  }
  return array;
}

struct thread_data
{
  double* array;
  int left;
  int right;
};

struct thread_data thread_data_array[NUM_THREADS];
pthread_t threads[NUM_THREADS];

void quickSortSequential(double arr[], int left, int right) {
  int i = left, j = right;
  double tmp;
  double pivot = arr[(left + right) / 2];

  /* partition */
  while (i <= j) {
    while (arr[i] < pivot)
      i++;
    while (arr[j] > pivot)
      j--;
    if (i <= j) {
      tmp = arr[i];
      arr[i] = arr[j];
      arr[j] = tmp;
      i++;
      j--;
    }
  };

  /* recursion */
  if (left < j)
    quickSortSequential(arr, left, j);
  if (i < right)
    quickSortSequential(arr, i, right);
}

void* quickSortSequentialWrapper(void *threadarg) {

  struct thread_data *my_data;
  my_data = (struct thread_data *) threadarg;

  int i = my_data->left, j = my_data->right;
  double * array = my_data->array;
  quickSortSequential(array, my_data->left, my_data->right);

}
/*
void quickSortSequentialLeft(double arr[], int left, int right) {
  int i = left, j = right;
  double tmp;
  double pivot = arr[(left + right) / 2];

  //partition
  while (i <= j) {
    while (arr[i] < pivot)
      i++;
    while (arr[j] > pivot)
      j--;
    if (i <= j) {
      tmp = arr[i];
      arr[i] = arr[j];
      arr[j] = tmp;
      i++;
      j--;
    }
  };

  // recursion
  if (left < j)
    quickSortSequentialLeft(arr, left, j);
  if (i < right)
    quickSortSequentialLeft(arr, i, right);
}

void* quickSortSequentialWrapperLeft(void *threadarg) {

  struct thread_data *my_data;
  my_data = (struct thread_data *) threadarg;

  int i = my_data->left, j = my_data->right;
  double * array = my_data->array;
  quickSortSequentialLeft(array, my_data->left, my_data->right);
}
*/



void* quickSort(void *threadarg) { //(double arr[], int left, int right) {

  int r;
  void* status;
  struct thread_data *my_data;


  my_data = (struct thread_data *) threadarg;

  int i = my_data->left, j = my_data->right;
  double * array = my_data->array;
  double tmp;
  double pivot = array[(i + j) / 2];
  unsigned int tid = (unsigned int)pthread_self();
  //cout << "for thread " << tid << " pivot is =" << pivot << endl;
  /* partition */
  while (i <= j) {
    while (array[i] < pivot)
      i++;
    while (array[j] > pivot)
      j--;
    if (i <= j) {
      tmp = array[i];
      array[i] = array[j];
      array[j] = tmp;
      i++;
      j--;
    }
  }



  //for (int j = 0; j < NUM_THREADS; ++j) {
   // r = pthread_join(threads[j], &status);
  //}


  if (my_data->left < j) {
    //quickSortSequential(array, my_data->left, j);
    thread_data_array[1].array = array;
    thread_data_array[1].left = my_data->left;
    thread_data_array[1].right = j;

    int rc = pthread_create(&threads[1], NULL, quickSortSequentialWrapper, (void *)&thread_data_array[1]);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }


    if (i < my_data->right) {
      //quickSortSequential(array, i, my_data->right);
      thread_data_array[2].array = array;
      thread_data_array[2].left = i;
      thread_data_array[2].right = my_data->right;

      int rc = pthread_create(&threads[2], NULL, quickSortSequentialWrapper, (void *)&thread_data_array[2]);
      if (rc) {
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
      }
    }



  }
  pthread_exit((void*) threadarg);
}


int main(int argc, char *argv[]) {

  //first cl argument specifies the nb of elements
  const int nbElements  = atoi(argv[1]);
  double* array = new double[nbElements];
  void* status;
  clock_t start, end;
  /* Initialize and set thread detached attribute */
  pthread_mutex_init(&mutexsum, NULL);
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);



  array = fillArray(array, nbElements);

  //cout << "array before sorting is :" << endl ;
  //for (int i = 0; i < nbElements; i++) {
  //cout << array[i] << endl ;
  //}


  int rc;

  thread_data_array[0].array = array;
  thread_data_array[0].left = 0;
  thread_data_array[0].right = nbElements - 1;

  start = clock();


  rc = pthread_create(&threads[0], &attr, quickSort, (void *)&thread_data_array[0]);
  if (rc) {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
  }



  int r;

  for (int j = 0; j < NUM_THREADS; ++j) {
    r = pthread_join(threads[j], &status);
  }

/* cout << "array after sorting is\n" ;
  for (int i = 0; i < nbElements; i++) {
    cout << array[i] << endl ;
  }
*/

  end = clock();

  float seconds = ((float)end - (float)start) / CLOCKS_PER_SEC;
  cout << "Pthreaded Quicksort time = " << seconds << " seconds" << endl;

  free(array);
  pthread_exit(NULL);
  return 0;


}