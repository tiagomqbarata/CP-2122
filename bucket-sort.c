// Bucket sort in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCKSIZE 16

void swap(int* a, int* b) ;
int partition (int arr[], int low, int high) ;
void quickSort(int arr[], int low, int high) ;
int getBucketIndex(int value, int interval) ;

// Sorting function
void bucketSort(int arr[], int nElementos, int maxRandomNumber, int nBuckets) {

  int i, j, k;
  int interval = maxRandomNumber/nBuckets;
  int lastIndex[nBuckets];

  // Inicialize lastIndex
  memset( lastIndex, 0, nBuckets*sizeof(int) );

  // Inicialize buckets and reserved space
  int **buckets = (int**) malloc(nBuckets * sizeof(int*));
  for (i = 0; i < nBuckets; ++i) {
    buckets[i] = (int*)malloc(nElementos*sizeof(int));
  }

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
      quickSort(buckets[i], 0, lastIndex[i]-1);
    
    
  // Put sorted elements on arr
  for (j = 0, i = 0; i < nBuckets; ++i) 
    for(k = 0; k < lastIndex[i]; k++ )
      arr[j++] = buckets[i][k];


  return;
}

int getBucketIndex(int value, int interval) {
  return value / interval;
}

// A utility function to swap two elements 
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

  for (i=0 , ptr = m ; i<100 ; i++ , ptr++) {
   // printf("%i %i\n", *ptr, m);
    printf("%i - ",*ptr );
	}
  printf ("\n");

  return 0;
}

