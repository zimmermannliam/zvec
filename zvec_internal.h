#ifndef ZVEC_INTERNAL_H
#define ZVEC_INTERNAL_H
/*******************************************************************************
 * by               Liam Zimmermann
 * 
 * file name	    zvec_internal.h
 *
 * description      ZVec internal logic header
 ******************************************************************************/
#include "type.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    TYPE * data;
    size_t size;
    size_t cap;
    size_t cap_multiplier;
} ZVec;

void zvec_check(ZVec * zv, const char * file, uint16_t line,
                const char * msg);


#endif
