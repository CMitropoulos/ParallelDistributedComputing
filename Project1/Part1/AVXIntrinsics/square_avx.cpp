#include <immintrin.h>
#include <stdio.h>
#include "timing.h"
double randomNum(int upper){
	return (double)rand() / RAND_MAX * upper;
}

int main() {
	const unsigned int totalNum = 20 * 1e6;
	const float firstGuess = 2.0f;
  	float* values = (float*)malloc(totalNum*sizeof(float));
	float* result = (float*)malloc(totalNum*sizeof(float));

	for(int i = 0; i < totalNum; i++){
		values[i] = randomNum(8);
		result[i] = 0.0;
	}

  __m256 valuesVec = _mm256_loadu_ps(values);
  __m256 resultVec = _mm256_loadu_ps(result);
  
  

reset_and_start_timer();
 //calculate the square root
 resultVec  =_mm256_sqrt_ps(valuesVec);

double dt = get_elapsed_mcycles();

//  float* val = (float*)&valuesVec;
//  printf("%f %f %f %f\n", val[0], val[1], val[2], val[3]);
	
 // float* res = (float*)&resultVec;
 // printf("%f %f %f %f\n", res[0], res[1], res[2], res[3]);
printf("@time of AVX run:\t\t\t[%.3f] million cycles\n", dt);
   
 
  return 0;
}
