#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define NUN_SIZE 36
#define ONE "1"
#define ZERO "0"

void
prime(int read_pipe, int write_pipe){
    char buf[NUN_SIZE];
    int val;

    read(read_pipe, buf, NUN_SIZE);
    for(int i=0; i<NUN_SIZE; i++){
        if(buf[i] != ZERO){
            val = i;
            break;
        }
    }
    printf("prime %d", val);
    buf[val] = ZERO;

    for(int i=0; i<NUN_SIZE; i++){
        if(i % val == 0){
            buf[i] = ZERO;
        }
    }



    int pid = fork();
    if(pid > 0){
        write(write_pipe, buf, NUN_SIZE);   
    }
    if(pid == 0){
        prime(read_pipe,write_pipe);
    }
}

void
main(int argc, char *argv[])
{
  char num[NUN_SIZE];
  char number;
  for(int i=0; i<NUN_SIZE; i++){
    num[i] = ONE;
  }

  if(argc != 1){
    printf("Error Example: sleep 2");
    exit(-1);
  }

    int fd[2];
    pipe(fd);
    int pid = fork();

    if(pid > 0){
        num[0] = ZERO;
        num[1] = ZERO;

        write(fd[1], num, NUN_SIZE);
        wait(0);
    }

    if(pid == 0){
        prime(fd[0], fd[1]);
        wait(0);
    }
}