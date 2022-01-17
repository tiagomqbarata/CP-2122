// Bucket sort in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

void swap(int* a, int* b) ;
int partition (int arr[], int low, int high) ;
void quickSort(int arr[], int low, int high) ;
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
  
  omp_set_num_threads(16);
  #pragma omp parallel num_threads(16)
  {
    // Inicialize buckets and reserved space
    #pragma omp for
    for (i = 0; i < nBuckets; ++i) {
      buckets[i] = (int*)malloc(nElementos*sizeof(int));
    }
  
    // Separate numbers by buckets
    #pragma omp for
    for (i = 0; i < nElementos; ++i) {
      int pos = getBucketIndex(arr[i], interval);
      #pragma omp critical
      buckets[pos][lastIndex[pos]++] = arr[i];
    }
  

//  #pragma omp barrier


  
    // Sort the elements of each bucket
    #pragma omp for
    for (i = 0; i < nBuckets; ++i) 
      if(lastIndex[i])
        quickSort(buckets[i], 0, lastIndex[i]-1);
  

  }
    j = 0;
    for (i = 0; i < nBuckets; ++i) {
      for(k = 0; k < lastIndex[i]; k++ )
        arr[j++] = buckets[i][k];
    }
 
  
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

void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 

/* This function takes last element as pivot, places 
the pivot element at its correct position in sorted 
array, and places all smaller (smaller than pivot) 
to left of pivot and all greater elements to right 
of pivot */
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high]; // pivot 
    int i = (low - 1), j; // Index of smaller element and indicates the right position of pivot found so far

    for ( j = low; j <= high - 1; j++){ 
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) 
        { 
            i++; // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 

/* The main function that implements QuickSort 
arr[] --> Array to be sorted, 
low --> Starting index, 
high --> Ending index */
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition(arr, low, high); 

        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
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
  int *ptr;
  int i;
  int nElems = 200;
  int maxElem = 1000;
  int nBuckets = 10;

  alloc_array(&m, nElems);


  for (i=0 , ptr = m ; i<nElems ; i++ , ptr++) {
   // printf("%i %i\n", *ptr, m);
    *ptr = (int) rand() % maxElem;
	}

  bucketSortParallel(m, nElems, maxElem, nBuckets);

  for (i=0, ptr=m ; i<nElems ; i++ , ptr ++) {
   // printf("%i %i\n", *ptr, m);
    printf("%i - ",*ptr );
	}
  printf ("\n");

  return 0;
}

*/