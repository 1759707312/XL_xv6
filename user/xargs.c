#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

#define MSGSIZE 16

int
main(int argc, char* argv[]){

    sleep(10); 

    // 获取上一个命令的标准化输入
    char buf[MSGSIZE];
    read(0, buf, MSGSIZE);

    // 获取命令行参数
    char* xargv[MSGSIZE];
    int xargc = 0;
    for (int i = 1; i < argc; i++)
    {
        /* code */
        xargv[xargc] = argv[i];
        xargc++;
    }
    char* p = buf;
    for (int i = 0; i < MSGSIZE; i++)
    {
        /* code */
        if(buf[i] == '\n'){
            int pid = fork();
            if(pid > 0){
                p = &buf[i+1];
                wait(0);
            }
            else{
                // 使用exec执行命令
                buf[i] = 0;
                xargv[xargc] = p;
                xargc++;
                xargv[xargc] = 0;
                xargc++;

                exec(xargv[0], xargv);
                exit(1);
            }
        }
    }
    wait(0);
    exit(0);
}