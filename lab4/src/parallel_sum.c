#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>

#include <sys/time.h>
#include <sys/types.h>

#include <getopt.h>
#include <pthread.h>

#include "sum.h"
#include "utils.h"

/*struct Sum_Args {
  int *array;
  int begin;
  int end;
};
*/
void *ThreadSum(void *args) {
  struct SumArgs *sum_args = (struct SumArgs *)args;
  return (void *)(size_t)Sum(sum_args);
}

int main(int argc, char **argv) {
  /*
   *  TODO:
   *  threads_num by command line arguments
   *  array_size by command line arguments
   *	seed by command line arguments
   */

  uint32_t threads_num = 0;
  uint32_t array_size = 0;
  uint32_t seed = 0;
  pthread_t threads[threads_num];
//-------------------------------------------start
while (true) {
      int current_optind = optind ? optind : 1;

      static struct option options[] = { {"seed", required_argument, 0, 0},
                                        {"array_size", required_argument, 0, 0},
                                        {"threads_num", required_argument, 0, 0},
                                        {0, 0, 0, 0} };

      int option_index = 0;
      int c = getopt_long(argc, argv, "f", options, &option_index);

      if (c == -1) break;

      switch (c) {
      case 0:
          switch (option_index) {
          case 0:
              seed = atoi(optarg);
              if (seed <= 0)
              {
                  printf("seed is a positive number\n\n");
                  return 1;
              }
              break;
          case 1:
              array_size = atoi(optarg);
              if (array_size <= 0)
              {
                  printf("array_size is a positive number\n");
                  return 1;
              }
              break;
          case 2:
              threads_num = atoi(optarg);
              if (array_size <= 0)
              {
                  printf("thread_num is a positive number\n");
                  return 1;
              }
              break;
         
          defalut:
              printf("Index %d is out of options\n", option_index);
          }
          break;

      case '?':
          break;

      default:
          printf("getopt returned character code 0%o?\n", c);
      }
  }
//-------------------------------------------end
  /*
   * TODO:
   * your code here
   * Generate array here
   */

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);

/*for(int i = 0;i < array_size;i++)
{
  printf("%d ",array[i]);
}
*/

//------------------------------------start
struct timeval start_time;
  gettimeofday(&start_time, NULL);

  int segment = array_size / threads_num;
  struct SumArgs args[threads_num];
  for (int i = 0; i < threads_num; i++) {
      args[i].begin = i * segment;
      args[i].end = (i == threads_num) ? array_size : (i + 1) * segment;
      args[i].array = array;
  }

  for (uint32_t i = 0; i < threads_num; i++) {
    if (pthread_create(&threads[i], NULL, ThreadSum, (void *)&args)) {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }

  int total_sum = 0;
  for (uint32_t i = 0; i < threads_num; i++) {
    int sum = 0;
    pthread_join(threads[i], (void **)&sum);
    total_sum += sum;
  }

  struct timeval finish_time;
  gettimeofday(&finish_time, NULL);

  double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;

  free(array);
  printf("Total: %d\n", total_sum);
  printf("Elapsed time: %fms\n", elapsed_time);
  return 0;
}
