#ifndef ZVEC_H
#define ZVEC_H
/*******************************************************************************
 * by               Liam Zimmermann
 * 
 * file name	    zvec.h
 *
 * description      zvec external header file
 ******************************************************************************/
#include <stdint.h>
#include "type.h"
typedef void* ZVec; 

ZVec * zvec_create(uint16_t cap);
void zvec_destroy(ZVec * zv);
void zvec_extend(ZVec * zv, size_t new_size);
void zvec_zero_fill(ZVec * zv, size_t begin, size_t end);
TYPE zvec_at(ZVec * zv, size_t loc);
void zvec_put(ZVec * zv, size_t loc, TYPE d);
size_t zvec_size(ZVec * zv);
void zvec_push(ZVec * zv, TYPE d);

#endif
