/**
 * @file `file.c` implements auxillary file handeling functions, in addition to
 * the basic functions in `stdio.h`.
 *
 * @author H Paterson.
 * @copyright BSL-1.0.
 * @date July 2020.
 */

#include "file.h"
#include <assert.h>

/**
 * Find the length of a file.
 * 
 * `file_length` finds the length of a file, without effecting the file state.
 *
 * @param file The file to inspect.
 * @return The length of `file`.
 */
long file_length(FILE* const file)
{
    assert(file != NULL);
    long initial_pos = ftell(file);
    assert(fseek(file, 0, SEEK_END) == 0);
    long length = ftell(file);
    assert(fseek(file, initial_pos, SEEK_SET) == 0);
    return length;
}
