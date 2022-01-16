#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "papi.h"

#include "bucket-sort.h"

static int verify_command_line (int argc, char *argv[], int *m_size, int *version);
static int alloc_array (int *m, int N);
static int init_array (int *m, int N, int max);
static int free_array (int *m);
static void print_usage (char *msg);
static int my_rand (int max);

#define NUM_EVENTS 4
int Events[NUM_EVENTS] = { PAPI_TOT_CYC, PAPI_TOT_INS, PAPI_L1_DCM, PAPI_L2_DCM};

// PAPI counters' values
long long values[NUM_EVENTS], min_values[NUM_EVENTS];

// number of times the function is executed and measured
#define NUM_RUNS 5

int main (int argc, char *argv[]) {
fprintf(stdout, "0");
  long long start_usec, end_usec, elapsed_usec, min_usec=0L;
  int m_size, total_elements, max_random, i, run;
  int *a;
  int num_hwcntrs = 0;

  if (!verify_command_line (argc, argv, &m_size, &max_random)) {
	  return 0;
  }
  total_elements = m_size;

  fprintf (stdout, "\nSetting up PAPI...");
  // Initialize PAPI 
  PAPI_library_init (PAPI_VER_CURRENT);

  /* Get the number of hardware counters available */
  if ((num_hwcntrs = PAPI_num_counters()) <= PAPI_OK)  {
    fprintf (stderr, "PAPI error getting number of available hardware counters!\n");
    return 0;
  }
  fprintf(stdout, "done!\nThis system has %d available counters.\n\n", num_hwcntrs);

  // We will be using at most NUM_EVENTS counters
  if (num_hwcntrs >= NUM_EVENTS) {
    num_hwcntrs = NUM_EVENTS;
  } else {
    fprintf (stderr, "Error: there aren't enough counters to monitor %d events!\n", NUM_EVENTS);
    return 0;
  }

  // create an instance for random function, with a constant seed
  srand(18);

  // ini A array
  fprintf (stdout, "Initializing Array A...");
  if (!init_array (a, total_elements, max_random)) return 0;
  fprintf (stdout, "done!\n");

printf("4");

  // warmup caches
  fprintf (stdout, "Warming up caches...");
//  bucketSort (a, m_size);
  fprintf (stdout, "done!\n");
printf("5");

  for (run=0 ; run < NUM_RUNS ; run++) { 
   fprintf (stderr, "\nrun=%d", run);

   // use PAPI timer (usecs) - note that this is wall clock time
   // for process time running in user mode -> PAPI_get_virt_usec()
   // real and virtual clock cycles can also be read using the equivalent
   // PAPI_get[real|virt]_cyc()
   start_usec = PAPI_get_real_usec();

   /* Start counting events */
   if (PAPI_start_counters(Events, num_hwcntrs) != PAPI_OK) {
     fprintf (stderr, "PAPI error starting counters!\n");
     return 0;
   }

  // bucketSort (a, m_size);


   /* Stop counting events */
   if (PAPI_stop_counters(values, NUM_EVENTS) != PAPI_OK) {
     fprintf (stderr, "PAPI error stoping counters!\n");
     return 0;
   }

   end_usec = PAPI_get_real_usec();
   fprintf (stderr, "done!\n");

   elapsed_usec = end_usec - start_usec;

   if ((run==0) || (elapsed_usec < min_usec)) {
      min_usec = elapsed_usec;
      for (i=0 ; i< NUM_EVENTS ; i++) min_values[i] = values [i];
   }

  } // end runs
  printf ("\nWall clock time: %lld usecs\n", min_usec);
  
  // output PAPI counters' values 
  for (i=0 ; i< NUM_EVENTS ; i++) {
	  char EventCodeStr[PAPI_MAX_STR_LEN];

	  if (PAPI_event_code_to_name(Events[i], EventCodeStr) == PAPI_OK) {
		fprintf (stdout, "%s = %lld\n", EventCodeStr, min_values[i]);
	  } else {
		fprintf (stdout, "PAPI UNKNOWN EVENT = %lld\n", min_values[i]);
	  }
  }

#if NUM_EVENTS > 1
  // evaluate CPI and Texec here
  if ((Events[0] == PAPI_TOT_CYC) && (Events[1] == PAPI_TOT_INS)) {
    float CPI = ((float) min_values[0]) / ((float) min_values[1]);
    fprintf (stdout, "CPI = %.2f\n", CPI);
  }
#endif

//  free_array (a);

  printf ("\nThat's all, folks\n");
  return 1;
}

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

int alloc_array (int *m, int N) {

m = (int*) malloc (N*sizeof(int));
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

	if (!alloc_array (m, N)) return 0;
	for (i=0 , ptr = m ; i<N ; i++ , ptr++) {
  //  *ptr = my_rand(max);
	}
	return 1;
} 

int free_array (int *m) {
  free (m);
  m = NULL;
  return 1;
}