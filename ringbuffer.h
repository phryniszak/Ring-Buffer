#include <stdint.h>
#include <stdbool.h>
/**
 * @file
 * Prototypes and structures for the ring buffer module.
 */

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

/**
 * The size of a ring buffer.
 * Due to the design only <tt> RING_BUFFER_SIZE-1 </tt> items
 * can be contained in the buffer.
 * The buffer size must be a power of two.
*/

/**
 * The type which is used to hold the size
 * and the indicies of the buffer.

 */
typedef uint32_t ring_buffer_size_t;

/**
 * Used as a modulo operator
 * as <tt> a % b = (a & (b − 1)) </tt>
 * where \c a is a positive index in the buffer and
 * \c b is the (power of two) size of the buffer.
 */
//#define rbuffer->mask (RING_BUFFER_SIZE - 1)

/**
 * Simplifies the use of <tt>struct ring_buffer_t</tt>.
 */
typedef struct ring_buffer_t ring_buffer_t;

/**
 * Structure which holds a ring buffer.
 * The buffer contains a buffer array
 * as well as metadata for the ring buffer.
 */
struct ring_buffer_t
{
  /** Index of tail. */
  ring_buffer_size_t tail_index;
  /** Index of head. */
  ring_buffer_size_t head_index;
  /** Mask. */
  ring_buffer_size_t mask;
  /** Is initialized. */
  bool initialized;
  /** Buffer memory. */
  char *buffer;
};

/**
 * Initializes the ring buffer pointed to by <em>buffer</em>.
 * This function can also be used to empty/reset the buffer.
 * @param rbuffer The ring buffer to initialize.
 * @param buffer Array storage.
 * @param size Size of buffer.
 * @return 1 succes - size is power of 2; 0 otherwise.
 */
bool ring_buffer_init(ring_buffer_t *rbuffer, char *buffer, ring_buffer_size_t size);

/**
 * Adds a byte to a ring buffer.
 * @param rbuffer The buffer in which the data should be placed.
 * @param data The byte to place.
 */
void ring_buffer_queue(ring_buffer_t *rbuffer, char data);

/**
 * Adds an array of bytes to a ring buffer.
 * @param rbuffer The buffer in which the data should be placed.
 * @param data A pointer to the array of bytes to place in the queue.
 * @param size The size of the array.
 */
void ring_buffer_queue_arr(ring_buffer_t *rbuffer, const char *data, ring_buffer_size_t size);

/**
 * Adds an array of bytes to a ring buffer.
 * WARNING: no check if enough space in buffer
 * @param rbuffer The buffer in which the data should be placed.
 * @param data A pointer to the array of bytes to place in the queue.
 * @param size The size of the array.
 */
void ring_buffer_queue_arr_fast(ring_buffer_t *rbuffer, const char *data, ring_buffer_size_t size);

/**
 * Returns the oldest byte in a ring buffer.
 * @param rbuffer The buffer from which the data should be returned.
 * @param data A pointer to the location at which the data should be placed.
 * @return 1 if data was returned; 0 otherwise.
 */
ring_buffer_size_t ring_buffer_dequeue(ring_buffer_t *rbuffer, char *data);

/**
 * Returns the <em>len</em> oldest bytes in a ring buffer.
 * @param rbuffer The buffer from which the data should be returned.
 * @param data A pointer to the array at which the data should be placed.
 * @param len The maximum number of bytes to return.
 * @return The number of bytes returned.
 */
ring_buffer_size_t ring_buffer_dequeue_arr(ring_buffer_t *rbuffer, char *data, ring_buffer_size_t len);

/**
 * Peeks a ring buffer, i.e. returns an element without removing it.
 * @param rbuffer The buffer from which the data should be returned.
 * @param data A pointer to the location at which the data should be placed.
 * @param index The index to peek.
 * @return 1 if data was returned; 0 otherwise.
 */
ring_buffer_size_t ring_buffer_peek(ring_buffer_t *rbuffer, char *data, ring_buffer_size_t index);

/**
 * Returns whether a ring buffer is empty.
 * @param rbuffer The buffer for which it should be returned whether it is empty.
 * @return 1 if empty; 0 otherwise.
 */
inline bool ring_buffer_is_empty(ring_buffer_t *rbuffer)
{
  return (rbuffer->head_index == rbuffer->tail_index);
}

/**
 * Returns whether a ring buffer is full.
 * @param rbuffer The buffer for which it should be returned whether it is full.
 * @return 1 if full; 0 otherwise.
 */
inline bool ring_buffer_is_full(ring_buffer_t *rbuffer)
{
  return ((rbuffer->head_index - rbuffer->tail_index) & rbuffer->mask) == rbuffer->mask;
}

/**
 * Returns the number of items in a ring buffer.
 * @param rbuffer The buffer for which the number of items should be returned.
 * @return The number of items in the ring buffer.
 */
inline ring_buffer_size_t ring_buffer_num_items(ring_buffer_t *rbuffer)
{
  return ((rbuffer->head_index - rbuffer->tail_index) & rbuffer->mask);
}

/**
 * Returns the number of bytes that can be written to the ring
 * buffer without overwriting
 * @param rbuffer The buffer for which the number of items should be returned.
 * @return Number of bytes that are free to write in the buffer.
 */
inline ring_buffer_size_t ring_buffer_num_wr_items(ring_buffer_t *rbuffer)
{
  return ((rbuffer->tail_index - rbuffer->head_index - 1) & rbuffer->mask);
}

#endif /* RINGBUFFER_H */