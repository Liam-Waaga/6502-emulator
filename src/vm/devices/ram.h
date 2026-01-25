

#ifndef RAM_H
#define RAM_H
#include "device.h"
#include <stddef.h>

typedef struct {
    Device dev;
    void *data;
    size_t data_size;
} RAM;



#endif