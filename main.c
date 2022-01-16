#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "papi.h"

#include "bucket-sort.h"

int verify_command_line (int argc, char *argv[], int *total_elements, int *version) {
	int val;

	if (argc!=3) {
		print_usage ((char *)"Exactly 2 arguments are required!");
		return 0;
	}

	val = atoi (argv[1]); // size of array

	if (val <= 0) {
		print_usage ((char *)"The array size must be a positive integer!");
		return 0;
	}
	else {
		*total_elements = val;// size of array
	}
		
	val = atoi (argv[2]);

	if (val <= 0) {
		print_usage ((char *)"The number of elem max must be a positive integer!");
		return 0;
	}
	else 
		*version = val;
		
	return 1;
}

void print_usage (char *msg) {
	fprintf (stderr, "Command Line Error! %s\n", msg);
	fprintf (stderr, "Usage:\tgemm <matrix size> <version>\n\n");
}

int alloc_matrix (int *m, int N) {

	m = (int *) malloc (N*sizeof(int));
	if (!(m)) {
		print_usage ((char *)"Could not allocate memory for array!");
		return 0;
	}
	return 1;
}

int my_rand (int max) {
  return rand() % max;
}

int init_array (int *m, int N, int max) {
 	int i;
	int *ptr;

	if (!alloc_matrix (m, N)) return 0;
	for (i=0 , ptr = m ; i<N ; i++ , ptr++) {
		*ptr = my_rand(max);
	}
	return 1;
} 

int free_array (int *m) {
  free (m);
  m = NULL;
  return 1;
}

int main (int argc, char *argv[]) {
printf("DEU\n\n");
}