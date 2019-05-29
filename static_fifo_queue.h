#ifndef C_STATIC_FIFO_QUEUE_H
#define C_STATIC_FIFO_QUEUE_H

#include <stdint.h>

// *** USER CONFIGURATION *** //
#define SFQ_CONFIG_STORAGE_WIDTH_TYPE   uint8_t
#define SFQ_CONFIG_STORAGE_LENGTH_TYPE  uint32_t

typedef SFQ_CONFIG_STORAGE_WIDTH_TYPE   storage_width_t;
typedef SFQ_CONFIG_STORAGE_LENGTH_TYPE  storage_length_t;

typedef struct{
    const void * storage;
    const storage_width_t storage_width;
    storage_length_t head;
    storage_length_t tail;
} sfqueue_t;

#endif // C_STATIC_FIFO_QUEUE_H