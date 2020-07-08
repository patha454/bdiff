/**
 * @file `buffer.c` implements a buffer data type.
 *
 * @see `buffer.h`
 *
 * @author H Paterson.
 * @copyright BSL-1.0.
 * @date July 2020.
 */

#include "buffer.h"
#include <assert.h>
#include <stdlib.h>

/**
 * @def DEFAULT_BUFFER_SIZE
 *
 * The default size of a new buffer, in bytes.
 */
#define DEFAULT_BUFFER_SIZE 256

/**
 * Create a new, empty buffer.
 *
 * @see `buffer.h`.
 * @return A pointer to the new buffer, or `NULL` on failure.
 */
extern struct Buffer* new_buffer()
{
    struct Buffer* buffer = malloc(sizeof *buffer);
    if (buffer == NULL) {
        return buffer;
    }
    buffer->allocated_length = DEFAULT_BUFFER_SIZE;
    buffer->length = 0;
    buffer->data = calloc(1, buffer->allocated_length);
    if (buffer->data == NULL) {
        buffer->allocated_length = 0;
        free(buffer);
        return 0;
    }
    return buffer;
}

/**
 * Deallocate an existing buffer.
 *
 * @see `buffer.h`.
 * @return A `NULL` pointer, as a convience to avoid dangeling referenced to
 *         the old buffer.
 */
extern struct Buffer* free_buffer(struct Buffer* const buffer)
{
    assert(buffer != NULL);
    assert(buffer->data != NULL);
    free(buffer->data);
    buffer->data = NULL;
    buffer->length = 0;
    buffer->allocated_length = 0;
    free(buffer);
    return NULL;
}

/**
 * Get the number of bytes stored in a buffer.
 *
 * @see `buffer.h`.
 * @param buffer The buffer to determine the length of.
 * @return The byte length of `buffer`.
 */
extern size_t buffer_length(const struct Buffer* const buffer)
{
    assert(buffer != NULL);
    return buffer->length;
}
