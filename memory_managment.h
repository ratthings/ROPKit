/**
 * File: memory_management.h
 *
 * Description:
 * Contains declarations for memory management function 'my_mallocarray' and
 * convenience macros 'MALLOCARRAY' and 'MALLOC'.
 *
 * Author: snocra5h@icloud.com
 * Date: July 14, 2023
 */

#ifndef MEMORY_MANAGMENT_H
#define MEMORY_MANAGMENT_H

#include <stdlib.h>

_Static_assert(((size_t)-1) > 0, "size_t must be an unsigned type");

/**
 * my_mallocarray() - Safely allocate memory for an array
 * @nmemb: Number of members in the array
 * @size: Size of each array member in bytes
 *
 * This function multiplies @nmemb by @size to calculate the total number of
 * bytes to allocate for the array. If this multiplication would result in an
 * overflow, it fails safely instead of causing undefined behavior.
 *
 * Rather than doing the multiplication and checking if the result is greater
 * than SIZE_MAX (which would overflow before the check), it checks if SIZE_MAX
 * divided by @nmemb is less than @size, which is mathematically equivalent but
 * doesn't overflow.
 *
 * If @nmemb is 0, it skips this check because no overflow is possible.
 *
 * On success, this function returns a pointer to the allocated memory, which is
 * initialized to zero. The caller is responsible for freeing the memory.
 * On failure, it prints an error message to stderr and terminates the program.
 */
void *my_mallocarray(size_t nmemb, size_t size);

// Convenience macros for using 'my_mallocarray'
#define MALLOCARRAY(n, type) ((type *)my_mallocarray(n, sizeof(type)))
#define MALLOC(type) MALLOCARRAY(1, type)

#endif // MEMORY_MANAGMENT_H
