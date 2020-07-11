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
#include "file.h"
#include <assert.h>

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
 * Create a new buffer from the contents of `file`.
 *
 * @param file The file to read in.
 * @return A buffer with the contents for `file`, or NULL on failure.
 */
extern struct Buffer* new_buffer_from_file(FILE* const file)
{
    size_t _file_length = 0;
    size_t file_position = 0;
    struct Buffer* buffer = NULL;

    _file_length = file_length(file);
    file_position = ftell(file);
    buffer = new_buffer();
    assert(buffer_realloc(buffer, _file_length));
    assert(fread(buffer->data, _file_length, 1, file) == 1);
    buffer->length = _file_length;
    assert(fseek(file, file_position, SEEK_SET) == 0);
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

/**
 * Gets the amount of memory allocated to a buffer.
 *
 * @param buffer The buffer to inspect.
 * @return The memory, in bytes, allocated to `buffer`.
 */
extern size_t buffer_allocated_length(const struct Buffer* const buffer)
{
    assert(buffer != NULL);
    return buffer->allocated_length;
}

/**
 * Resizes a buffer to a new length.
 *
 * @warning Resizing to a smaller buffer than the current length will truncate
 * the data in the buffer.
 *
 * @note Resizing to a larger size that the current length will allocate and
 * zero memory, but not change the `length` variable indicating the length of
 * the data.
 *
 * @param buffer The buffer to resize.
 * @param length The new length, in bytes, to resize the buffer to.
 * @return 1 on success, 0 on failure.
 */
extern uint_fast8_t buffer_realloc(struct Buffer* const buffer, size_t new_length)
{
    long delta = 0;
    assert(buffer != NULL);
    delta = (long)(new_length - buffer->length);
    buffer->allocated_length = new_length;
    buffer->data = realloc(buffer->data, buffer->allocated_length);
    if (buffer->data == NULL) {
        buffer->length = 0;
        buffer->allocated_length = 0;
        return 0;
    }
    if (delta < 0) {
        buffer->length = new_length;
    } else {
        memset(&((char*)(buffer->data))[buffer->length], 0, delta);
    }
    return 1;
}

/**
 * Adds data to the end of a buffer.
 *
 * @param buffer The buffer to add data to.
 * @param data The data to add to the buffer.
 * @param length The length, in bytes, of the `data` being added.
 * @return The new length of the buffer, or 0 on failure.
 */
extern size_t buffer_append(struct Buffer* const buffer, const void* const data, size_t length)
{
    assert(buffer != NULL);
    assert(data != NULL);
    if (buffer_length(buffer) + length < buffer_allocated_length(buffer)) {
        if (!buffer_realloc(buffer, buffer->length + length)) {
            return 0;
        }
    }
    memcpy(&((char*)buffer->data)[buffer->length], data, length);
    buffer->length += length;
    return 0;
}
