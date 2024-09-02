
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
main(int argc, char *argv[])
{
  int time;

  if(argc != 2){
    printf("Error Example: sleep 2");
    exit(-1);
  }
  time = atoi(argv[1]);

  if (sleep(time) < 0) {
    printf("Can not sleep!");
    exit(-1);
  }
  exit(0);
}