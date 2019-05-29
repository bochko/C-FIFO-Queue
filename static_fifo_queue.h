#ifndef C_STATIC_FIFO_QUEUE_H
#define C_STATIC_FIFO_QUEUE_H

#include <stdint.h>
#include <stddef.h>

// *** USER CONFIGURATION *** //
#define SFQ_WIDTH_TYPE   size_t
#define SFQ_LENGTH_TYPE  size_t

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

/// sfq_create_queue : Creates a new queue based on a pre-allocated storage space,
/// store type width, and maximum length
/// \param storage pointer to pre-allocated storage space; must be large enough to hold
///        storage_width * max_length size of data
/// \param storage_width width in bytes of data type to be stored in queue
/// \param max_length maximum number of items to be stored in queue
/// \return an sfqueue_t type, instantiated with the specified parameters; the returned queue
///         must be checked with sfq_check_queue as this function does not return error codes
sfqueue_t sfq_create_queue(const void* storage, SFQ_WIDTH_TYPE storage_width, SFQ_LENGTH_TYPE max_length);

/// sfq_check_queue : Checks if a queue has properly instantiated members. The storage pointer,
/// storage width and maximum length of the queue are checked to not be NULL/zero values
/// \param queue pointer to queue to be checked
/// \return returns SFQ_ERR_ARG if the queue does not conform to sanity check, and SFQ_ERR_OK
///         otherwise
sfqueue_err_t sfq_check_queue(const sfqueue_t* queue);

/// sfq_enqueue : Enqueue an item in the queue passed
/// \param queue pointer to destination queue
/// \param source pointer to item
/// \return returns SFQ_ERR_FULL if there is no space in the queue, SFQ_ERR_ARG
///         if the pointer to the queue or source are NULL, and SFQ_ERR_OK otherwise
sfqueue_err_t sfq_enqueue(sfqueue_t* queue, void* source);

/// sfq_dequeue : Dequeue an item from the queue passed
/// \param queue pointer to source queue
/// \param destination pointer to pre-allocated item storage; must be large enough to hold
///        storage_width size of data
/// \return returns SFQ_ERR_EMPTY if there is no next item in the queue, SFQ_ERR_ARG
///         if the pointer to the queue or destination are NULL, and SFQ_ERR_OK
///         otherwise
sfqueue_err_t sfq_dequeue(sfqueue_t* queue, void* destination);

/// sfq_remaining : Returns the number of items remaining in the queue
/// \param queue pointer to source queue
/// \return Returns zero if queue is empty or does not pass sfq_check_queue with SFQ_ERR_OK,
///         or the number of remaining items in the queue otherwise
SFQ_LENGTH_TYPE sfq_remaining(sfqueue_t* queue);

#endif // C_STATIC_FIFO_QUEUE_H