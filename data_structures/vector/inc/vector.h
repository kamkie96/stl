#ifndef __VECTOR_H__
#define __VECTOR_H__

/***********************************************/
/****************** Includes *******************/
/***********************************************/

#include <stddef.h>

/***********************************************/
/***************** Structures ******************/
/***********************************************/

typedef struct vector_t {
    size_t __size__;
    size_t __capacity__;
    size_t __elementSize__;
    void* __vectorArray_p__;
} vector_t;

/***********************************************/
/**************** Declarations *****************/
/***********************************************/

vector_t* init(const size_t elementSize);

int clear(vector_t* vector_p);

int insert(vector_t* restrict vector_p, 
           const void* const restrict inputData_p);

int delete(vector_t* restrict vector_p,
           void* restrict outputData_p);

#endif /* __VECTOR_H__ */
