#include "static_fifo_queue.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

sfqueue_t sfq_create_queue(const void* storage, SFQ_WIDTH_TYPE storage_width, SFQ_LENGTH_TYPE max_length)
{
    sfqueue_t queue = {0U};
    if((storage != NULL) && (storage_width != 0U) && (max_length != 0U))
    {
        queue.storage = (void*)storage;
        queue.max_length = max_length;
    }
    return queue;
}

sfqueue_err_t sfq_check_queue(const sfqueue_t* queue)
{
    sfqueue_err_t ret = SFQ_ERR_OK;
    if((queue->storage == NULL)
    || (queue->max_length == (SFQ_LENGTH_TYPE) 0U)
    || (queue->storage_width == (SFQ_WIDTH_TYPE) 0U))
    {
        ret = SFQ_ERR_ARG;
    }
    return ret;
}

sfqueue_err_t sfq_enqueue(sfqueue_t* queue, void* source)
{
    sfqueue_err_t ret = SFQ_ERR_OK;
    if((queue == NULL) || (source == NULL))
    {
        ret = SFQ_ERR_ARG;
    }
    else if(queue->length >= (SFQ_LENGTH_TYPE) queue->max_length)
    {
        ret = SFQ_ERR_FULL;
    }
    else
    {
        uint8_t* target = &(((uint8_t*)queue->storage)[queue->tail * queue->storage_width]);
        SFQ_WIDTH_TYPE storage_idx;
        for(storage_idx = (SFQ_WIDTH_TYPE) 0U; storage_idx < queue->storage_width; storage_idx++)
        {
            target[storage_idx] = ((uint8_t*)source)[storage_idx];
        }
        queue->length++;
        queue->tail++;
        if(queue->tail >= queue->max_length)
        {
            queue->tail = (SFQ_LENGTH_TYPE) 0U;
        }
    }
    return ret;
}

sfqueue_err_t sfq_dequeue(sfqueue_t* queue, void* destination)
{
    sfqueue_err_t ret = SFQ_ERR_OK;
    if((queue == NULL) || (destination == NULL))
    {
        ret = SFQ_ERR_ARG;
    }
    else if(queue->length == (SFQ_LENGTH_TYPE) 0U)
    {
        ret = SFQ_ERR_EMPTY;
    }
    else
    {
        uint8_t* source = &(((uint8_t*)queue->storage)[queue->head * queue->storage_width]);
        SFQ_WIDTH_TYPE storage_idx;
        for(storage_idx = (SFQ_WIDTH_TYPE) 0U; storage_idx < queue->storage_width; storage_idx++)
        {
            ((uint8_t*)destination)[storage_idx] = source[storage_idx];
        }
        queue->head++;
        queue->length--;
        if(queue->head >= queue->max_length)
        {
            queue->head = (SFQ_LENGTH_TYPE) 0U;
        }
    }
    return ret;
}

SFQ_LENGTH_TYPE sfq_remaining(sfqueue_t* queue)
{
    SFQ_LENGTH_TYPE ret = (SFQ_LENGTH_TYPE) 0U;
    sfqueue_err_t err = sfq_check_queue(queue);
    if(err == SFQ_ERR_OK)
    {
        ret = queue->length;
    }
    return ret;
}
