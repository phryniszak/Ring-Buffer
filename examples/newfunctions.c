#include <assert.h>
#include <stdio.h>
#include "../ringbuffer.h"

int main(void)
{
    /* Create and initialize 128 byte ring buffer */
    char buff128[128];
    ring_buffer_t ring_buffer128;
    ring_buffer_init(&ring_buffer128, buff128, sizeof(buff128));

    /* Create and initialize 128 byte ring buffer */
    char buff64[64];
    ring_buffer_t ring_buffer64;
    ring_buffer_init(&ring_buffer64, buff64, sizeof(buff64));

    ring_buffer_size_t items;

    items = ring_buffer_num_items(&ring_buffer128);
    printf("buffer128 writen bytes %d\n", items);
    assert(items == 0);

    items = ring_buffer_num_items(&ring_buffer64);
    printf("buffer64 writen bytes %d\n", items);
    assert(items == 0);

    items = ring_buffer_num_wr_items(&ring_buffer128);
    printf("buffer128 bytes2write %d\n", items);
    assert(items == 127);

    items = ring_buffer_num_wr_items(&ring_buffer64);
    printf("buffer64 bytes2write bytes %d\n", items);
    assert(items == 63);

    printf("Add array of 20 bytes\n");
    ring_buffer_queue_arr(&ring_buffer64, "Hello, Ring Buffer!", 20);
    ring_buffer_queue_arr(&ring_buffer128, "Hello, Ring Buffer!", 20);

    items = ring_buffer_num_items(&ring_buffer128);
    printf("buffer128 writen bytes: %d\n", items);
    assert(items == 20);

    items = ring_buffer_num_items(&ring_buffer64);
    printf("buffer64 writen bytes: %d\n", items);
    assert(items == 20);

    items = ring_buffer_num_wr_items(&ring_buffer128);
    printf("buffer128 bytes2write: %d\n", items);
    assert(items == 107);

    items = ring_buffer_num_wr_items(&ring_buffer64);
    printf("buffer64 bytes2write: %d\n", items);
    assert(items == 43);

    /* Add elements to buffer; one at a time */
    for (int i = 0; i < 46; i++)
    {
        if (ring_buffer_is_full(&ring_buffer64))
        {
            items = ring_buffer_num_items(&ring_buffer64);
            printf("buffer64 writen bytes: %d\n", items);
        }
        else
        {
            ring_buffer_queue(&ring_buffer64, i);
            items = ring_buffer_num_wr_items(&ring_buffer64);
            printf("added 1 element; buffer64 bytes2write: %d\n", items);
        }
    }

    for (int i = 0; i < 110; i++)
    {
        if (ring_buffer_is_full(&ring_buffer128))
        {
            items = ring_buffer_num_items(&ring_buffer128);
            printf("buffer128 writen bytes: %d\n", items);
        }
        else
        {
            ring_buffer_queue(&ring_buffer128, i);
            items = ring_buffer_num_wr_items(&ring_buffer128);
            printf("added 1 element; buffer128 bytes2write: %d\n", items);
        }
    }
}
