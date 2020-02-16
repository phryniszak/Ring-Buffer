#include "ringbuffer.h"

/**
 * @file
 * Implementation of ring buffer functions.
 */

bool ring_buffer_init(ring_buffer_t *rbuffer, char *buffer, ring_buffer_size_t size)
{
  // https://stackoverflow.com/questions/600293/how-to-check-if-a-number-is-a-power-of-2
  if ((size != 0) && ((size & (size - 1)) == 0))
  {

    rbuffer->tail_index = 0;
    rbuffer->head_index = 0;
    rbuffer->buffer = buffer;
    rbuffer->mask = size - 1;
    rbuffer->initialized = true;
    return true;
  }

  rbuffer->tail_index = 0;
  rbuffer->head_index = 0;
  rbuffer->buffer = 0;
  rbuffer->mask = 0;
  rbuffer->initialized = false;
  return false;
}

void ring_buffer_queue(ring_buffer_t *rbuffer, char data)
{
  /* Is buffer full? */
  if (ring_buffer_is_full(rbuffer))
  {
    /* Is going to overwrite the oldest byte */
    /* Increase tail index */
    rbuffer->tail_index = ((rbuffer->tail_index + 1) & rbuffer->mask);
  }

  /* Place data in buffer */
  rbuffer->buffer[rbuffer->head_index] = data;
  rbuffer->head_index = ((rbuffer->head_index + 1) & rbuffer->mask);
}

void ring_buffer_queue_arr(ring_buffer_t *rbuffer, const char *data, ring_buffer_size_t size)
{
  /* Add bytes; one by one */
  ring_buffer_size_t i;
  for (i = 0; i < size; i++)
  {
    ring_buffer_queue(rbuffer, data[i]);
  }
}

void ring_buffer_queue_arr_fast(ring_buffer_t *rbuffer, const char *data, ring_buffer_size_t size)
{
  /* Add bytes; one by one */
  ring_buffer_size_t i;
  for (i = 0; i < size; i++)
  {
    /* Place data in buffer */
    rbuffer->buffer[rbuffer->head_index] = data[i];
    rbuffer->head_index = ((rbuffer->head_index + 1) & rbuffer->mask);
  }
}

ring_buffer_size_t ring_buffer_dequeue(ring_buffer_t *rbuffer, char *data)
{
  if (ring_buffer_is_empty(rbuffer))
  {
    /* No items */
    return 0;
  }

  *data = rbuffer->buffer[rbuffer->tail_index];
  rbuffer->tail_index = ((rbuffer->tail_index + 1) & rbuffer->mask);
  return 1;
}

ring_buffer_size_t ring_buffer_dequeue_arr(ring_buffer_t *rbuffer, char *data, ring_buffer_size_t len)
{
  if (ring_buffer_is_empty(rbuffer))
  {
    /* No items */
    return 0;
  }

  char *data_ptr = data;
  ring_buffer_size_t cnt = 0;
  while ((cnt < len) && ring_buffer_dequeue(rbuffer, data_ptr))
  {
    cnt++;
    data_ptr++;
  }
  return cnt;
}

ring_buffer_size_t ring_buffer_peek(ring_buffer_t *rbuffer, char *data, ring_buffer_size_t index)
{
  if (index >= ring_buffer_num_items(rbuffer))
  {
    /* No items at index */
    return 0;
  }

  /* Add index to pointer */
  ring_buffer_size_t data_index = ((rbuffer->tail_index + index) & rbuffer->mask);
  *data = rbuffer->buffer[data_index];
  return 1;
}

extern inline bool ring_buffer_is_empty(ring_buffer_t *rbuffer);
extern inline bool ring_buffer_is_full(ring_buffer_t *rbuffer);
extern inline ring_buffer_size_t ring_buffer_num_items(ring_buffer_t *rbuffer);
extern inline ring_buffer_size_t ring_buffer_num_wr_items(ring_buffer_t *rbuffer);