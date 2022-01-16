// Bucket sort in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void swap(int* a, int* b) ;
int partition (int arr[], int low, int high) ;
void quickSort(int arr[], int low, int high) ;
int getBucketIndex(int value, int interval) ;

// Sorting function
void bucketSort(int arr[], int size, int nBuckets) {

  int i, j;
  int interval = size/nBuckets;
  int lastIndex[size];

  memset( lastIndex, 0, size*sizeof(int) );

  int **buckets = (int**) malloc(nBuckets * sizeof(int*));

  for (i = 0; i < nBuckets; ++i) {
    buckets[i] = (int*)malloc(size*sizeof(int));
  }

  for (i = 0; i < size; ++i) {
    int pos = getBucketIndex(arr[i], interval);

    buckets[pos][lastIndex[pos]++] = arr[i];
  }

  for(i=0; i<nBuckets; i++){
    printf("Brucket %d: ", i);
    for(j = 0; j < lastIndex[i]; j++){
      printf("%d - ", buckets[i][j]);
    }
    printf("nElems: %d \n\n", lastIndex[i]);
  }

  // Sort the elements of each bucket
  for (i = 0; i < nBuckets; ++i) {
    if(lastIndex[i]){
      quickSort(buckets[i], 0, lastIndex[i]-1);
    }
  }

  // Put sorted elements on arr
  for (j = 0, i = 0; i < nBuckets; ++i) {
    for(int k = 0; k < lastIndex[i]; k++)
      arr[j++] = buckets[i][k];
  }

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
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++) 
    { 
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
  int size = 100, max = 100;
  int *a;



  for(int i = 0; i < size; i++){
    a[i] = rand() % max;
    printf("%d - ", a[i]);
  }


  bucketSort(a,size);
  printf("\n\n\n ");
  for(int i = 0; i < size; i++){
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

  alloc_array(&m, 100);

  for (i=0 , ptr = m ; i<100 ; i++ , ptr++) {
   // printf("%i %i\n", *ptr, m);
    *ptr = (int) rand() % 100;
	}

  bucketSort(m, 100,10);

  for (i=0 , ptr = m ; i<100 ; i++ , ptr++) {
   // printf("%i %i\n", *ptr, m);
    printf("%i - ",*ptr );
	}
  return 0;
}

