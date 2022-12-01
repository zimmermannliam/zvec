/**********************************************************************
 * by               Liam Zimmermann
 * 
 * file name	    code.c
 *
 * description      sample code file
 *
 * header(s)        zvec.h
                    zvec_internal.h
**********************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "zvec_internal.h"

ZVec * zvec_create(size_t cap)
/**********************************************************************
 * description:     initialize a ZVec
 *
 * arguments:       cap     capacity that the zvec is initialized with
 *
 * return:          a new zvec
 * 
 * side effects:    NONE
**********************************************************************/
{
    ZVec * zv = malloc(sizeof(ZVec));
    zv->size = 0;
    zv->cap  = cap;
    zv->data = malloc(cap * sizeof(TYPE));
    zv->cap_multiplier = 2;
    return zv;
}

void zvec_destroy(ZVec ** zv)
/**********************************************************************
 * description:     destroy a ZVec
 *
 * arguments:       zv  zvector to destroy
 *
 * return:          NONE
 * 
 * side effects:    zv is now free()d.
**********************************************************************/
{
    zvec_check((*zv), __FILE__, __LINE__, NULL);
    free((*zv)->data);
    (*zv)->data = NULL;
    free(*zv);
    *zv = NULL;
}

void zvec_extend(ZVec * zv, size_t new_size)
/**********************************************************************
 * description:     extend zvec by a multiplier
 *
 * arguments:       zv      zvec to extend the data of
 *                  mul     multiplier to 
 *
 * return:          NONE
 * 
 * side effects:    zv data has loc 
**********************************************************************/
{
    zvec_check(zv, __FILE__, __LINE__, NULL);
    zv->data = realloc(zv->data, new_size);
}

void zvec_error(const char * msg, const char * file, uint16_t line)
/**********************************************************************
 * description:     error message and then exit
 *
 * arguments:       msg     message to be displayed
 *                  file    file in which error occured (likely 
 *                          __FILE__)
 *                  line    line on which error occured (likely 
 *                          __LINE__)
 *                  
 *
 * return:          NONE
 * 
 * side effects:    program exits
**********************************************************************/
{
    fprintf(stderr, "zvec ERROR: file %s line %d: %s", file, line, msg);
    exit(EXIT_FAILURE);
}

void zvec_check(ZVec * zv, const char * file, uint16_t line,
                const char * msg)
/**********************************************************************
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
 **********************************************************************/
{
    if(zv == NULL)
    {
        if(msg != NULL)
            fprintf(stderr, "%s\n", msg);
        zvec_error("NULL zvector", file, line);
    }
    if(zv->data == NULL)
    {
        if(msg != NULL)
            fprintf(stderr, "%s\n", msg);
        zvec_error("NULL data", file, line);
    }
    if(zv->size > zv->cap)
    {
        if(msg != NULL)
            fprintf(stderr, "%s\n", msg);
        zvec_error("capacity-size mismatch", file, line);
    }
}

void zvec_zero_fill(ZVec * zv, size_t begin, size_t end)
/**********************************************************************
 * description:     fills zvec with zero from index begin to one
 *                  before end
 *                  for example, to fill all unused data you would use
 *                  zvec_zero_fill(zv, zv->size, zv->cap)
 *
 * arguments:       zv      zvec to zero fill
 *                  begin   address to start filling at
 *                  end     address to stop filling at
 *
 * return:          NONE
 * 
 * side effects:    zv is filled from begin to end
**********************************************************************/
{
    size_t i = 0;

    zvec_check(zv, __FILE__, __LINE__, NULL);

    if(begin > zv->cap || end > zv->cap)
        zvec_error("tried to zero-fill past capacity", 
                    __FILE__, __LINE__);
    if(begin > end)
        zvec_error("zero_fill begin greater than zero_fill end",
                    __FILE__, __LINE__);

    for(i = begin; i < end; ++i)
        zv->data[i] = ZERO;

    if(zv->size < end)
            zv->size = end;
}

TYPE zvec_at(ZVec * zv, size_t loc)
/**********************************************************************
 * description:     retrieve data from zv at location loc
 *
 * arguments:       zv      zvec to retrieve from
 *                  loc     location in array to retrieve from
 *
 * return:          the data at location loc
 * 
 * side effects:    NONE
**********************************************************************/
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

void zvec_put(ZVec * zv, TYPE d, size_t loc)
/**********************************************************************
 * description:     put d at loc in zv. 
 *
 * arguments:       zv      zvec to put data in
 *                  d       data to put in  
 *                  loc     location in array to put in
 *
 * return:          NONE
 * 
 * side effects:    zv data has loc 
**********************************************************************/
{
    zvec_check(zv, __FILE__, __LINE__, NULL);
    if(loc > zv->size)
    {
        if(zv->cap > SIZE_MAX / zv->cap_multiplier)
        {
                zvec_extend(zv, (size_t) (zv->cap * zv->cap_multiplier));
                zvec_zero_fill(zv, zv->size, zv->cap);
                zvec_check(zv, __FILE__, __LINE__, NULL);
        }
        else
        {
            zvec_error("Tried to extend zvector cap too far, did you"
                       " set the cap multiplier too high?",
                       __FILE__, __LINE__);
        }
    }
    zv->data[loc] = d;
}

