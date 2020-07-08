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

#include <stddef.h>

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

#endif
