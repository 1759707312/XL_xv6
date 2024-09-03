#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc != 1){
        printf("Error Example: pingpong 1");
        exit(-1);
    }

    char content;

    int fd[2];
    pipe(fd);

    int pid;
    
    if (fork() == 0){   // child program
        pid = getpid();
        read(fd[0], &content, 1);
        close(fd[0]);
        printf("%d:received ping\n", pid);

        write(fd[1], "0", 1);
        close(fd[1]);
    }
    else{   // parent program
        pid = getpid();
        write(fd[1], "1", 1);
        close(fd[1]);

        read(fd[0], &content, 1);
        close(fd[0]);
        printf("%d:received pong\n", pid);
    }

    exit(0);
}