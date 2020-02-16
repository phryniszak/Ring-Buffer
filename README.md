Ring-Buffer
===========

A simple ring buffer (circular buffer) designed for embedded systems.

16/02/2020

Ring bugffers can have different sizes as long size is 2^n. Declare size during initilizetion.

new functions:

/**
 * Adds an array of bytes to a ring buffer.
 * WARNING: no check if enough space in buffer
 * @param rbuffer The buffer in which the data should be placed.
 * @param data A pointer to the array of bytes to place in the queue.
 * @param size The size of the array.
 */
void ring_buffer_queue_arr_fast(ring_buffer_t *rbuffer, const char *data, ring_buffer_size_t size);


/**
 * Returns the number of bytes that can be written to the ring
 * buffer without overwriting
 * @param rbuffer The buffer for which the number of items should be returned.
 * @return Number of bytes that are free to write in the buffer.
 */
inline ring_buffer_size_t ring_buffer_num_wr_items(ring_buffer_t *rbuffer);
