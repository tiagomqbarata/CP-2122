// Bucket sort in C

#include <stdio.h>
#include <stdlib.h>

#define NBUCKET 10  // Number of buckets
#define INTERVAL 10  // Each bucket capacity

struct Node {
  int data;
  struct Node *next;
};

struct Node *InsertionSort(struct Node *list);
void print(int arr[], int size);
void printBuckets(struct Node *list);
int getBucketIndex(int value);

// Sorting function
void bucketSort(int arr[], int size) {

  int i, j;
  struct Node **buckets;

  // Create buckets and allocate memory size
  buckets = (struct Node **)malloc(sizeof(struct Node *) * NBUCKET);

  // Initialize empty buckets
  for (i = 0; i < NBUCKET; ++i) {
    buckets[i] = NULL;
  }

  // Fill the buckets with respective elements
  for (i = 0; i < size; ++i) {
    struct Node *current;
    int pos = getBucketIndex(arr[i]);
    current = (struct Node *)malloc(sizeof(struct Node));
    current->data = arr[i];
    current->next = buckets[pos];
    buckets[pos] = current;
  }

  // Sort the elements of each bucket
  for (i = 0; i < NBUCKET; ++i) {
    buckets[i] = InsertionSort(buckets[i]);
  }

  // Put sorted elements on arr
  for (j = 0, i = 0; i < NBUCKET; ++i) {
    struct Node *node;
    node = buckets[i];
    while (node) {
      arr[j++] = node->data;
      node = node->next;
    }
  }

  return;
}

// Function to sort the elements of each bucket
struct Node *InsertionSort(struct Node *list) {
  
  struct Node *k, *nodeList;
  if (list == 0 || list->next == 0) {
    return list;
  }

  nodeList = list;
  k = list->next;
  nodeList->next = 0;
  while (k != 0) {
    struct Node *ptr;
    if (nodeList->data > k->data) {
      struct Node *tmp;
      tmp = k;
      k = k->next;
      tmp->next = nodeList;
      nodeList = tmp;
      continue;
    }

    for (ptr = nodeList; ptr->next != 0; ptr = ptr->next) {
      if (ptr->next->data > k->data)
        break;
    }

    if (ptr->next != 0) {
      struct Node *tmp;
      tmp = k;
      k = k->next;
      tmp->next = ptr->next;
      ptr->next = tmp;
      continue;
    } else {
      ptr->next = k;
      k = k->next;
      ptr->next->next = 0;
      continue;
    }
  }
  return nodeList;
}

int getBucketIndex(int value) {
  return value / INTERVAL;
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
/*
int alloc_array (int *m, int N) {

  *m = (int*) malloc (N*sizeof(int));

}


int main(int argc, char const *argv[])
{
  int *m;
  int *ptr;
  int i;

  alloc_array(&m, 100);

  for (i=0 , ptr = m ; i<100 ; i++ , ptr++) {
   // printf("%i %i\n", *ptr, m);
    *ptr = (int) rand() % 100;
	}

  for (i=0 , ptr = m ; i<100 ; i++ , ptr++) {
   // printf("%i %i\n", *ptr, m);
    printf("%i - ",*ptr );
	}
  return 0;
}
*/