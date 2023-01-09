/*******************************************************************************
 * by               Liam Zimmermann
 * 
 * file name	    code.c
 *
 * description      sample code file
 *
 * header(s)        zvec.h
 *                  zvec_internal.h
 ******************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "zvec_internal.h"

ZVec * zvec_create(size_t cap)
/*******************************************************************************
 * description:     initialize a ZVec
 *
 * arguments:       cap     capacity that the zvec is initialized with
 *
 * return:          a new zvec
 * 
 * side effects:    NONE
 ******************************************************************************/
{
    ZVec * zv = malloc(sizeof(ZVec));
    assert(cap != 0);
    zv->size = 0;
    zv->cap  = cap;
    zv->data = malloc(cap * sizeof(TYPE));
    zv->cap_multiplier = 2;

    return zv;
}

void zvec_destroy(ZVec * zv)
/*******************************************************************************
 * description:     destroy a ZVec
 *
 * arguments:       zv  
 *
 * return:          NONE
 * 
 * side effects:    zv is now free()d.
 ******************************************************************************/
{
    zvec_check(zv, __FILE__, __LINE__, NULL);
    free(zv->data);
    zv->data = NULL;
    free(zv);
}

void zvec_extend(ZVec * zv, size_t new_size)
/*******************************************************************************
 * description:     extend zvec by a multiplier
 *
 * arguments:       zv          zvec to extend the data of
 *                  new_size    new size to extend zv to 
 *
 * return:          NONE
 * 
 * side effects:    zv is extended to new size
 ******************************************************************************/
{
    
    zvec_check(zv, __FILE__, __LINE__, NULL);
    zv->data = (TYPE *) realloc(zv->data, new_size * sizeof(TYPE));
    zvec_check(zv, __FILE__, __LINE__, NULL);
    zv->cap = new_size;
}

void zvec_check(ZVec * zv, const char * file, uint16_t line,
                const char * msg)
/*******************************************************************************
 * description:     check a ZVec for whether it's NULL or not, error
 *                  out if NULL.
 *
 * arguments:       zv      zvector to check
 *                  line    put in __LINE__
 *                  file    put in __FILE__
 *                  msg     extra message to display (NULL if nothing)
 *
 * return:          NONE
 * 
 * side effects:    may exit failure. 
 ******************************************************************************/
{
    if(zv == NULL || zv->data == NULL || zv->size > zv->cap)
    {
        fprintf(stderr, "ZVec error: file %s line %u\n", file, line);
        if(msg)
            fprintf(stderr, "%s\n", msg);
    }
    assert(zv != NULL);
    assert(zv->data != NULL);
    assert(zv->size <= zv->cap);
}


TYPE zvec_at(ZVec * zv, size_t loc)
/*******************************************************************************
 * description:     retrieve data from zv at location loc
 *
 * arguments:       zv      zvec to retrieve from
 *                  loc     location in array to retrieve from
 *
 * return:          the data at location loc
 * 
 * side effects:    NONE
 ******************************************************************************/
{
    zvec_check(zv, __FILE__, __LINE__, NULL);
    if(loc < zv->size)
    {
        return zv->data[loc];
    }
    else
    {
        fprintf(stderr, "zvec: zvec_at() tries to access data beyond "
                        "array size\n");
        exit(EXIT_FAILURE);
    }
}

size_t zvec_push(ZVec * zv, TYPE d)
/*******************************************************************************
 * description:     Push some data into the next free slot of zvec
 *
 * arguments:       zv      zvec to push onto
 *                  d       data to be pushed
 *
 * return:          NONE
 * 
 * side effects:    data is added to zvec; size may extend.
 ******************************************************************************/
{
    zvec_check(zv, __FILE__, __LINE__, NULL);
    if(zv->size >= zv->cap)
    {
        zvec_extend(zv, zv->cap * zv->cap_multiplier);
    }
    zv->data[zv->size++] = d;

    return zv->size - 1;
}

void zvec_put(ZVec * zv, size_t loc, TYPE d)
/*******************************************************************************
 * description:     put d at loc in zv. 
 *
 * arguments:      zv      zvec to put data in
 *                  loc     location in array to put in
 *                  d       data to put in  
 *
 * return:          NONE
 * 
 * side effects:    zv data has loc 
 ******************************************************************************/
{
    zvec_check(zv, __FILE__, __LINE__, NULL);
    assert(loc < zv->size);

    zv->data[loc] = d;
}

size_t zvec_size(ZVec * zv)
/*******************************************************************************
 * description:     get size of a zvec
 *
 * arguments:       zv      zvec to get the size of
 *
 * return:          size of zv
 * 
 * side effects:    NONE
 ******************************************************************************/
{
    return zv->size;
}
