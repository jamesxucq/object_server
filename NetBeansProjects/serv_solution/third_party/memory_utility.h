#ifndef MEMORY_UTILITY_H_
#define MEMORY_UTILITY_H_

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#include <stdlib.h>

void *new_array(unsigned long num, unsigned int size, int use_calloc);
void *realloc_array(void *ptr, unsigned int size, size_t num);

#ifdef	__cplusplus
}
#endif

#endif /* MEMORY_UTILITY_H_ */

