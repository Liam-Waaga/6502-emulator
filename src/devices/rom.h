#ifndef ROM_H
#define ROM_H
#include "../types.h"

#include <stddef.h>


typedef struct {
    int fd; /* file on disc */
    size_t size;
} ROM;


#endif