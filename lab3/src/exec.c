#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  int proid = fork(); //
  if(proid < 0)
  {
    printf("Error\n");
  }
  if(proid == 0)
  {
    execv("sequential_min_max", argv);
    return 0;
  }

  wait(NULL);
  return 0;
}