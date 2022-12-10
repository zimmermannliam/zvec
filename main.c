#include <stdio.h>
#include <stdlib.h>
#include "zvec.h"

int main()
{
    uint16_t i;
    ZVec * zv = (ZVec *) zvec_create(16);
    for(i = 0; i < 16; ++i)
    {
        zvec_put(zv, i, i);
    }
    for(i = 0; i < zvec_size(zv); ++i)
    {
        printf("%u ", zvec_at(zv, i));
    }
    zvec_destroy(zv);
    return 0;
}
