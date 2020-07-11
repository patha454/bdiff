/**
 * @file `buffer.h` provides a buffer data type.
 *
 * A buffer is fat pointer to the underlying data.
 *
 * The `struct Buffer` can be used directly. Convience functions are
 * provided to manipulate the buffer.
 *
 * @author H Paterson.
 * @copyright BSL-1.0.
 * @date July 2020.
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * `Buffer` is a fat pointer containing data, data length, and allocated
 * length.
 */
struct Buffer {
    /** The data stored in the buffer. */
    void* data;

    /**
     * The number of bytes stored in the array.
     *
     * @note Indexes into `data` including and beyond length as data has not
     * been written to them (to read), and memory may not have been allocated
     * (to write).
     */
    size_t length;

    /** The number of bytes allocated to the pointer `data`. */
    size_t allocated_length;
};

/**
 * Creates a new, empty buffer.
 *
 * @return A new and empty buffer, or `NULL` on failure.
 */
extern struct Buffer* new_buffer();

/**
 * Create a new buffer from the contents of `file`.
 *
 * @param file The file to read in.
 * @return A buffer with the contents for `file`, or NULL on failure.
 */
extern struct Buffer* new_buffer_from_file(FILE* file);

/**
 * Free and deallocate a buffer.
 *
 * @param buffer The buffer to deallocate.
 * @return A null pointer, convenient for avoiding dangeling pointers to the
 *         original buffer.
 */
extern struct Buffer* free_buffer(struct Buffer* buffer);

/**
 * Gets the length of a buffer.
 *
 * @param buffer The buffer to determine the length of.
 * @return The length, in bytes, of `buffer`.
 */
extern size_t buffer_length(const struct Buffer* buffer);

/**
 * Gets the amount of memory allocated to a buffer.
 *
 * @param buffer The buffer to inspect.
 * @return The memory, in bytes, allocated to `buffer`.
 */
extern size_t buffer_allocated_length(const struct Buffer* buffer);

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
extern uint_fast8_t buffer_realloc(struct Buffer* buffer, size_t new_length);

/**
 * Adds data to the end of a buffer.
 *
 * @param buffer The buffer to add data to.
 * @param data The data to add to the buffer.
 * @param length The length, in bytes, of the `data` being added.
 */
extern size_t buffer_append(struct Buffer* buffer, const void* data, size_t length);

#endif
