#include <stdio.h>
#include <stdlib.h>
#include "zvec.h"

int main()
{
    uint16_t i = 0;
    ZVec * zv = (ZVec *) zvec_create(9);
    for(i = 0; i < 10; ++i)
    {
        zvec_push(zv, i);
    }
    for(i = 0; i < 10; ++i)
    {
        printf("%u ", zvec_at(zv, i));
    }
    printf("\n");
    zvec_destroy(zv);

    return 0;
}
