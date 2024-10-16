#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int
main()
{
    int a = 0;
    a = 1;
    // $1 = 0x8000000000087f49
    char *new_memory = (char *)sbrk(1);
    // $4 = 0x8000000000087f64
    a = 2;
    if(new_memory == (char *) -1){
        printf("sbrk failed to allocate memory.\n");
        exit(-1);
    } else {
        printf("Allocated 1 byte of memory at address: %p\n", new_memory);
    }

    *new_memory = 'A';
    printf("Value at allocated memory: %c\n", *new_memory);

    exit(0);
}
