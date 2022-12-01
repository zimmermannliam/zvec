#ifndef ZVEC_H
#define ZVEC_H
/**********************************************************************
 * by               Liam Zimmermann
 * 
 * file name	    zvec.h
 *
 * description      zvec external header file
**********************************************************************/
#include <stdint.h>
typedef void* ZVec; 

ZVec * zvec_create(uint16_t cap);
void zvec_destroy(ZVec ** zv);
void zvec_extend(ZVec * zv, size_t new_size);

#endif
