#include<stdio.h>
#include "dfs_stack.h"

int
main(void)
{
    int range;

    fprintf(stdout, "Please input the range:");
    fscanf(stdin, "%d", &range);

    dfs_stack(range);
    return 0;
}
