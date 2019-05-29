#ifndef C_STATIC_FIFO_QUEUE_H
#define C_STATIC_FIFO_QUEUE_H

#include <stdint.h>

// *** USER CONFIGURATION *** //
#define SFQ_WIDTH_TYPE   uint8_t
#define SFQ_LENGTH_TYPE  uint32_t

// *** LIBRARY CODE *** //

typedef struct{
    void * storage;
    SFQ_WIDTH_TYPE storage_width;
    SFQ_LENGTH_TYPE max_length;
    SFQ_LENGTH_TYPE length;
    SFQ_LENGTH_TYPE head;
    SFQ_LENGTH_TYPE tail;
} sfqueue_t;

typedef enum{
    SFQ_ERR_OK = 0U,
    SFQ_ERR_FULL,
    SFQ_ERR_EMPTY,
    SFQ_ERR_ARG
}sfqueue_err_t;

sfqueue_t sfq_create_queue(const void* storage, SFQ_WIDTH_TYPE storage_width, SFQ_LENGTH_TYPE max_length);
sfqueue_err_t sfq_check_queue(const sfqueue_t* queue);
sfqueue_err_t sfq_enqueue(sfqueue_t* queue, void* source);
sfqueue_err_t sfq_dequeue(sfqueue_t* queue, void* destination);
SFQ_LENGTH_TYPE sfq_remaining(sfqueue_t* queue);

#endif // C_STATIC_FIFO_QUEUE_H
