#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int
main()
{
    char *new_memory = (char *)sbrk(1);

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
