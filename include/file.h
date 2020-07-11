/**
 * @file `file.g` provides auxillary file handeling functions, in addition to
 * the basic functions in `stdio.h`.
 *
 * @author H Paterson.
 * @copyright BSL-1.0.
 * @date July 2020.
 */

#include <stdio.h>

#ifndef FILE_H_
#define FILE_H_

/**
 * Find the length of a file.
 * 
 * `file_length` finds the length of a file, without effecting the file state.
 *
 * @param file The file to inspect.
 * @return The length of `file`.
 */
size_t file_length(FILE* file);

#endif
