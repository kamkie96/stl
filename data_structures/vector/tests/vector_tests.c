/***********************************************/
/****************** Includes *******************/
/***********************************************/

#include <vector.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

/***********************************************/
/******************* Macros ********************/
/***********************************************/

#define SIZE_OF_ARRAY(array) sizeof(array) / sizeof(array[0])

/***********************************************/
/************** Static functions ***************/
/***********************************************/

static void 
printVectorOfUint32(const vector_t* const vector_p)
{
	uint32_t* vectorArray = (uint32_t*)vector_p->__vectorArray_p__;
	for (size_t i = 0; i < vector_p->__capacity__; i++)
	{
		(void)printf("%u ", vectorArray[i]);
	}
	(void)printf("\n");
}

static void 
printVectorOfDouble(const vector_t* const vector_p)
{
	double* vectorArray = (double*)vector_p->__vectorArray_p__;
	for (size_t i = 0; i < vector_p->__capacity__; i++)
	{
		(void)printf("%lf ", vectorArray[i]);
	}
	(void)printf("\n");
}

/***********************************************/
/***************** Unit tests ******************/
/***********************************************/

static void
testInitAndClearFunctions(void)
{
	const size_t sizeOfUint32 = sizeof(uint32_t);

	vector_t* vector_p = init(sizeOfUint32);
	assert(vector_p);

	assert(vector_p->__size__ == 0);
	assert(vector_p->__capacity__ == 0);
	assert(vector_p->__elementSize__ == sizeOfUint32);
	assert(!vector_p->__vectorArray_p__);
	assert(clear(vector_p) == 0);

	const size_t sizeOfDouble = sizeof(double);
	vector_p = init(sizeOfDouble);

	assert(vector_p->__size__ == 0);
	assert(vector_p->__capacity__ == 0);
	assert(vector_p->__elementSize__ == sizeOfDouble);
	assert(!vector_p->__vectorArray_p__);
	assert(clear(vector_p) == 0);
}

static void 
testSingleInsertFunction(void)
{
	const size_t sizeOfUint32 = sizeof(uint32_t);

	vector_t* vector_p = init(sizeOfUint32);
	assert(vector_p);

	const uint32_t exampleUint32 = 73;

	assert(insert(vector_p, &exampleUint32) == 0);
	assert(((uint32_t*)vector_p->__vectorArray_p__)[0] == exampleUint32);
	assert(vector_p->__size__ == 1);
	assert(vector_p->__capacity__ == 2);
	assert(vector_p->__vectorArray_p__);
	assert(clear(vector_p) == 0);

	const size_t sizeOfDouble = sizeof(double);

	vector_p = init(sizeOfDouble);
	assert(vector_p);

	const double exampleDouble = 73.7373;

	assert(insert(vector_p, &exampleDouble) == 0);
	assert(((double*)vector_p->__vectorArray_p__)[0] == exampleDouble);
	assert(vector_p->__size__ == 1);
	assert(vector_p->__capacity__ == 2);
	assert(vector_p->__vectorArray_p__);
	assert(clear(vector_p) == 0);
}

static void
testMultipleInsertFunction(void)
{
	const size_t sizeOfUint32 = sizeof(uint32_t);

	vector_t* vector_p = init(sizeOfUint32);
	assert(vector_p);

	const uint32_t arrayOfUint32[] =
	{
		2, 3, 5, 7, 11, 13, 17, 19
	};

	for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfUint32); ++i)
	{
		assert(vector_p->__size__ == i);
		assert(insert(vector_p, &arrayOfUint32[i]) == 0);
		assert(((uint32_t*)vector_p->__vectorArray_p__)[i] == arrayOfUint32[i]);
	}

	assert(vector_p->__size__ == SIZE_OF_ARRAY(arrayOfUint32));
	assert(vector_p->__capacity__ == vector_p->__size__);

	printVectorOfUint32(vector_p);
	assert(clear(vector_p) == 0);

	const size_t sizeOfDouble = sizeof(double);

	vector_p = init(sizeOfDouble);
	assert(vector_p);

	const double arrayOfDouble[] =
	{
		2.73, 3.73, 5.73, 7.73, 11.73, 13.73, 17.73, 19.73
	};

	for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfDouble); ++i)
	{
		assert(vector_p->__size__ == i);
		assert(insert(vector_p, &arrayOfDouble[i]) == 0);
		assert(((double*)vector_p->__vectorArray_p__)[i] == arrayOfDouble[i]);
	}

	assert(vector_p->__size__ == SIZE_OF_ARRAY(arrayOfDouble));
	assert(vector_p->__capacity__ == vector_p->__size__);

	printVectorOfDouble(vector_p);
	assert(clear(vector_p) == 0);
}

static void
testSingleInsertAndDeleteFunction(void)
{
	const size_t sizeOfUint32 = sizeof(uint32_t);

	vector_t* vector_p = init(sizeOfUint32);
	assert(vector_p);

	const uint32_t exampleUint32Value = 73;

	assert(insert(vector_p, &exampleUint32Value) == 0);

	assert(vector_p->__size__ == 1);
	assert(vector_p->__capacity__ == 2);
	assert(vector_p->__vectorArray_p__);

	uint32_t expectedUint32Value = 0;
	assert(delete(vector_p, &expectedUint32Value) == 0);

	assert(expectedUint32Value == exampleUint32Value);
	assert(vector_p->__size__ == 0);
	assert(vector_p->__capacity__ == 0);
	assert(!vector_p->__vectorArray_p__);
	assert(clear(vector_p) == 0);

	const size_t sizeOfDouble = sizeof(double);

	vector_p = init(sizeOfDouble);
	assert(vector_p);

	const double exampleDoubleValue = 73.7373;

	assert(insert(vector_p, &exampleDoubleValue) == 0);

	assert(vector_p->__size__ == 1);
	assert(vector_p->__capacity__ == 2);
	assert(vector_p->__vectorArray_p__);

	double expectedDoubleValue = 0;
	assert(delete(vector_p, &expectedDoubleValue) == 0);

	assert(expectedDoubleValue == exampleDoubleValue);
	assert(vector_p->__size__ == 0);
	assert(vector_p->__capacity__ == 0);
	assert(!vector_p->__vectorArray_p__);
	assert(clear(vector_p) == 0);
}

static void
testMultipleDeleteFunction(void)
{
	const size_t sizeOfUint32 = sizeof(uint32_t);

	vector_t* vector_p = init(sizeOfUint32);
	assert(vector_p);

	const uint32_t arrayOfUint32[] = 
	{
		2, 3, 5, 7
	};

	for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfUint32); ++i)
	{
		assert(insert(vector_p, &arrayOfUint32[i]) == 0);
	}

	uint32_t expectedUint32Value = 0;
	for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfUint32); ++i)
	{
		assert(delete(vector_p, &expectedUint32Value) == 0);
		assert(expectedUint32Value == arrayOfUint32[SIZE_OF_ARRAY(arrayOfUint32) - 1 -i]);
	}

	assert(vector_p->__size__ == 0);
	assert(vector_p->__capacity__ == 0);
	assert(!vector_p->__vectorArray_p__);
	assert(clear(vector_p) == 0);
}

int 
main(void)
{
	testInitAndClearFunctions();
	testSingleInsertFunction();
	testMultipleInsertFunction();
	testSingleInsertAndDeleteFunction();
	testMultipleDeleteFunction();
	return 0;
}
