/***********************************************/
/****************** Includes *******************/
/***********************************************/

#include <vector.h>
#include <stdlib.h>
#include <string.h>

/***********************************************/
/******************* Macros ********************/
/***********************************************/

#define FREE(ptr) \
    do { \
        free(ptr); \
        ptr = NULL; \
    } while (0)

#define RATIO 2

/***********************************************/
/**************** Implementation ***************/
/***********************************************/

vector_t* 
init(const size_t elementSize)
{
    if (elementSize == 0)
    {
        return NULL;
    }

    vector_t* vector_p = (vector_t*)malloc(sizeof(vector_t));

    if (!vector_p)
    {
        return NULL;
    }

    vector_p->__size__ = 0;
    vector_p->__capacity__ = 0;
    vector_p->__elementSize__ = elementSize;
    vector_p->__vectorArray_p__ = NULL;

    return vector_p;
}

int 
clear(vector_t* vector_p)
{
    if (!vector_p)
    {
        return -1;
    }

    if (vector_p->__vectorArray_p__)
    {
        FREE(vector_p->__vectorArray_p__);
    }

    FREE(vector_p);
    return 0;
}

int 
insert(vector_t* restrict vector_p, 
       const void* const restrict inputData_p)
{
    if (!vector_p)
    {
        return -1;
    }

    if (vector_p->__capacity__ == 0)
    {
        vector_p->__vectorArray_p__ = malloc(vector_p->__elementSize__ * RATIO);
        vector_p->__capacity__ = RATIO;
    }

    if (vector_p->__size__ == vector_p->__capacity__)
    {
        vector_p->__vectorArray_p__ = realloc(vector_p->__vectorArray_p__, 
                                              vector_p->__capacity__ * vector_p->__elementSize__ * RATIO);

        if (!vector_p->__vectorArray_p__)
        {
            return -1;
        }

        vector_p->__capacity__ *= RATIO;
    }

    void* srcAddr_p = (char*)vector_p->__vectorArray_p__ +
                      (vector_p->__size__ * vector_p->__elementSize__);

    (void)memcpy(srcAddr_p, 
                 inputData_p, 
                 vector_p->__elementSize__);
    
    ++vector_p->__size__;    
    return 0;
}

int 
delete(vector_t* restrict vector_p,
       void* restrict outputData_p)
{
    if (!vector_p && !vector_p->__vectorArray_p__)
    {
        return -1;
    }         

    --vector_p->__size__; 

    if (outputData_p)
    {
        const void* destAddr_p = (char*)vector_p->__vectorArray_p__ +
                                 ((vector_p->__size__) * vector_p->__elementSize__);   
        (void)memcpy(outputData_p, 
                     destAddr_p, 
                     vector_p->__elementSize__);
    }

    if (vector_p->__size__ == 0 && vector_p->__capacity__ == RATIO)
    {
        vector_p->__capacity__ = 0;
        FREE(vector_p->__vectorArray_p__);
        return 0;
    } 

    if (vector_p->__size__ == vector_p->__capacity__ / (2 * RATIO))
    {
        vector_p->__vectorArray_p__ = realloc(vector_p->__vectorArray_p__, 
                                              (vector_p->__capacity__ / RATIO) * vector_p->__elementSize__);

        if (!vector_p->__vectorArray_p__)
        {
            return -1;
        }

        vector_p->__capacity__ /= RATIO;
    }
     
    return 0;
}