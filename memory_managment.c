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
