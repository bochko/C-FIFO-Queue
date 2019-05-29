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
    if((queue->storage == NULL) || (queue->max_length == 0U) || (queue->storage_width == 0U))
    {
        ret = SFQ_ERR_ARG;
    }
    return ret;
}

sfqueue_err_t sfq_enqueue(sfqueue_t* queue, void* item)
{
    sfqueue_err_t ret = SFQ_ERR_OK;
    if((queue == NULL) || (item == NULL))
    {
        ret = SFQ_ERR_ARG;
    }
    else if(queue->length >= queue->max_length)
    {
        ret = SFQ_ERR_FULL;
    }
    else
    {
        uint8_t* target = &(((uint8_t*)queue->storage)[queue->tail * queue->storage_width]);
        SFQ_WIDTH_TYPE storage_idx;
        for(storage_idx = 0U; storage_idx < queue->storage_width; storage_idx++)
        {
            target[storage_idx] = ((uint8_t*)item)[storage_idx];
        }
        queue->length++;
        queue->tail++;
        if(queue->tail >= queue->max_length)
        {
            queue->tail = 0U;
        }
    }
    return ret;
}

