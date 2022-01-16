// Bucket sort in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void partition(int *arr, int *i, int *j);
void quickSort(int *arr, int size) ;
void partition_internel(int *arr, int *i, int *j);
void quickSort_internel(int *arr, int left, int right) ;
int getBucketIndex(int value, int interval) ;
int position(int lastIndex[], int i);


// Sorting function
void bucketSortParallel(int arr[], int nElementos, int maxRandomNumber, int nBuckets) {
  
  int i, j, k;
  int interval = maxRandomNumber/nBuckets;
  int lastIndex[nBuckets];

  // Inicialize lastIndex
  memset( lastIndex, 0, nBuckets*sizeof(int) );
  
  int **buckets = (int**) malloc(nBuckets * sizeof(int*));
  
  #pragma omp parallel num_threads(16)
  #pragma omp for schedule(dynamic)
    // Inicialize buckets and reserved space
    for (i = 0; i < nBuckets; ++i) {
      buckets[i] = (int*)malloc(nElementos*sizeof(int));
    }
  
  #pragma omp parallel num_threads(16)
  #pragma omp for schedule(dynamic)
    // Separate numbers by buckets
    for (i = 0; i < nElementos; ++i) {
      int pos = getBucketIndex(arr[i], interval);
      buckets[pos][lastIndex[pos]++] = arr[i];
    }
  

/*
  for(i=0; i<nBuckets; i++){
    printf("Brucket %d: ", i);
    for(j = 0; j < lastIndex[i]; j++){
      printf("%d - ", buckets[i][j]);
    }
    printf("nElems: %d \n\n", lastIndex[i]);
  }
*/

  // Sort the elements of each bucket
  for (i = 0; i < nBuckets; ++i) 
    if(lastIndex[i])
      quickSort(buckets[i], lastIndex[i]-1);

  #pragma omp parallel num_threads(16)
  #pragma omp parallel for
    // Put sorted elements on arr
    for (i = 0; i < nBuckets; ++i) 
      #pragma omp task 
      j = position(lastIndex, i);
      for(k = 0; k < lastIndex[i]; k++ )
        arr[j++] = buckets[i][k];

  return;
}

int position(int lastIndex[], int i){
  int j, sum = 0;
  for(j = 0; j < i; j++)
    sum += lastIndex[j];

  return sum;
}

int getBucketIndex(int value, int interval) {
  return value / interval;
}

void quickSort(int *arr, int size) 
{

	int i = 0, j = size;
  	/* PARTITION PART */
  partition(arr, &i, &j);
	#pragma omp parallel
	#pragma omp single
	{
    if (0 < j){
      #pragma omp task 
      quickSort_internel(arr, 0, j);
    }
    if (i< size){
      #pragma omp task
      quickSort_internel(arr, i, size);
    }
	}
}

void partition(int *arr, int *i, int *j){
	//float pivot = arr[((*j)+(*i)) / 2];
	int pivot = arr[(*j)];
	while ((*i) <= (*j)) {
		while (arr[(*i)] < pivot)
			(*i)++;
		while (arr[(*j)] > pivot)
			(*j)--;
		if ((*i) <= (*j)) {
			int tmp = arr[(*i)];
			arr[(*i)] = arr[(*j)];
			arr[(*j)] = tmp;
			(*i)++;
			(*j)--;
		}
	}
}

void partition_internel(int *arr, int *i, int *j){
	//float pivot = arr[((*j)+(*i)) / 2];
	int pivot = arr[(*j)];
	while ((*i) <= (*j)) {
		while (arr[(*i)] < pivot)
			(*i)++;
		while (arr[(*j)] > pivot)
			(*j)--;
		if ((*i) <= (*j)) {
			int tmp = arr[(*i)];
			arr[(*i)] = arr[(*j)];
			arr[(*j)] = tmp;
			(*i)++;
			(*j)--;
		}
	}
}

void quickSort_internel(int* arr, int left, int right) 
{
	int i = left, j = right;
  	/* PARTITION PART */
        partition_internel(arr, &i, &j) ;

	/* RECURSION PART */
	if (left < j){ 
        	quickSort_internel(arr, left, j);
    	}
	if (i< right){
        	quickSort_internel(arr, i, right);
    	}
}



/*
int main(int argc, char const *argv[])
{
  int nElementos = 100, maxRandomNumber = 100;
  int *a;



  for(int i = 0; i < nElementos; i++){
    a[i] = rand() % maxRandomNumber;
    printf("%d - ", a[i]);
  }


  bucketSort(a,nElementos);
  printf("\n\n\n ");
  for(int i = 0; i < nElementos; i++){
    printf("%d - ", a[i]);
  }
}
*/ 



/*


int alloc_array (int **m, int N) {

  *m = (int*) malloc (N*sizeof(int));

}

int main(int argc, char const *argv[])
{
  int *m;
  int *ptr, *teste;
  int i;
  int nElems = 200;
  int maxElem = 1000;
  int nBuckets = 10;

  alloc_array(&m, nElems);

  for (i=0 , ptr = m ; i<nElems ; i++ , ptr++) {
   // printf("%i %i\n", *ptr, m);
    *ptr = (int) rand() % maxElem;
	}

  bucketSort(m, nElems, maxElem, nBuckets);

  for (i=0 , ptr = m ; i<nElems ; i++ , ptr++) {
   // printf("%i %i\n", *ptr, m);
    printf("%i - ",*ptr );
	}
  printf ("\n");

  return 0;
}

*/