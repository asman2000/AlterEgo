#ifndef ALTEREGO_TYPES_H
#define ALTEREGO_TYPES_H

/*--------------------------------------------------------------------------*/

#include <exec/types.h>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

enum Returns
{
	RT_OK = 0,
	RT_FAILED_OPEN_DOS,
	RT_FAILED_OPEN_GFX,
};

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_TYPES_H */
