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

#define NUM_THREADS     3

using namespace std;


double* fillArray(double* array, int nbElements){
  //generate random numbers to fill the array
  int upper =100; //max number allowed
  random_device rd; // obtain a random number from hardware
  mt19937 eng(rd()); // seed the generator
  uniform_real_distribution<> distr(0,100); 
  for (int i=0; i< nbElements;i++){
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

void* quickSort(void *threadarg){//(double arr[], int left, int right) {
      
      void* status;
      struct thread_data *my_data;
      my_data = (struct thread_data *) threadarg;

      int i = my_data->left, j = my_data->right;
      double * array = my_data->array;
      double tmp;
      double pivot = array[(i+j) / 2];
     // cout << "pivot is =" <<pivot <<endl;
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
      };
    /* Initialize and set thread detached attribute */
      pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   

    int rc1;

  thread_data_array[1].array = array;
  thread_data_array[1].left = my_data->left;
  thread_data_array[1].right = j;


rc1 = pthread_create(&threads[1], &attr, quickSort, (void *)&thread_data_array[1]);
       if (rc1){
          printf("ERROR; return code from pthread_create() is %d\n", rc1);
          exit(-1);
       }



      rc1 = pthread_join(threads[1], &status);
       if (rc1) {
          cout<< "ERROR; return code from pthread_join() is" << rc1 <<endl;
          exit(-1);
          }
       printf("Main: completed join with thread 1 having a status of %ld\n", (long)status);


    

    int rc2;

  thread_data_array[2].array = array;
  thread_data_array[2].left = i;
  thread_data_array[2].right = my_data->right;


rc2 = pthread_create(&threads[2], &attr, quickSort, (void *)&thread_data_array[2]);
       if (rc2){
          printf("ERROR; return code from pthread_create() is %d\n", rc2);
          exit(-1);
       }


      rc2 = pthread_join(threads[2], &status);
       if (rc2) {
          cout<< "ERROR; return code from pthread_join() is" << rc2 <<endl;
          exit(-1);
          }
       printf("Main: completed join with thread 2 having a status of %ld\n", (long)status);
       

       
      /*
  struct thread_data *ldata; 
  ldata->array = arr;
  ldata->left = left;
  ldata->right = j;
     //recursion
      if (&left < j)
          int rc = pthread_create(thread_id, NULL, quickSort, (void *)&ldata);
          if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
          }
  struct thread_data *rdata; 
  rdata->array = arr;
  rdata->left = i;
  rdata->right = right;  
      if (i < &right)
          int rc = pthread_create(thread_id, NULL, quickSort, (void *)&rdata);
          if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
          }*/
            pthread_exit((void*) threadarg);
}


int main(int argc, char *argv[]){
  
  //first cl argument specifies tj nb of elements
  const int nbElements  = atoi(argv[1]); 
  double* array = new double[nbElements];
  void* status;
    clock_t start, end;
    /* Initialize and set thread detached attribute */
      pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   

  array = fillArray(array, nbElements);


  
  int rc;

  thread_data_array[0].array = array;
  thread_data_array[0].left = 0;
  thread_data_array[0].right = nbElements -1;

start=clock();
rc = pthread_create(&threads[0], &attr, quickSort, (void *)&thread_data_array[0]);
       if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
       }

end=clock();

      rc = pthread_join(threads[0], &status);
       if (rc) {
          cout<< "ERROR; return code from pthread_join() is" << rc <<endl;
          exit(-1);
          }
       printf("Main: completed join with thread 0 having a status of %ld\n", (long)status);
       
 


  
 

  float seconds = ((float)end-(float)start)/ CLOCKS_PER_SEC;
    cout<< "Pthreaded Quicksort time = "<< seconds << " seconds" << endl;
    
pthread_exit(NULL);
    return 0;


}