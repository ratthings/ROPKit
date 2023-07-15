/**
 * File: memory_management.c
 *
 * Description:
 * This file contains the implementation of the memory management function
 * declared in memory_management.h. This function, 'my_mallocarray', allocates
 * memory safely, avoiding overflow.
 *
 * Author: snocra5h@icloud.com
 * Date: July 15, 2023
 */

#include "memory_managment.h"

#include <stdint.h>
#include <stdio.h>

void *my_mallocarray(size_t nmemb, size_t size) {
  if (nmemb && SIZE_MAX / nmemb < size) {
    fprintf(stderr, "Error: size overflow\n");
    exit(EXIT_FAILURE);
  }

  return calloc(nmemb, size);
}
