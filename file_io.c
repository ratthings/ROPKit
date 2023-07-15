/**
 * File: file_io.c
 *
 * Description:
 * Contains implementations for file I/O functions as declared in file_io.h.
 * These functions include 'get_next_line' and 'prompt_user_and_open_file'.
 *
 * Author: snocra5h@icloud.com
 * Date: July 15, 2023
 */

#include "file_io.h"
#include "memory_managment.h"

#include <stdlib.h>
#include <string.h>

// clang-format off
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on

char *get_next_line(FILE *fp)
{
	char buffer[MAX_BUFFER], *s = NULL, *ret = NULL;

	s = fgets(buffer, ARRAY_SIZE(buffer), fp);
	if (s == NULL) {
		if (feof(fp)) {
			clearerr(fp);
			return NULL;
		} else {
			perror("fgets() error");
			clearerr(fp);
			fclose(fp);
			exit(EXIT_FAILURE);
		}
	}

	ret = MALLOCARRAY(strlen(buffer) + 1, char);
	if (ret == NULL) {
		perror("malloc() error");
		exit(EXIT_FAILURE);
	}

	strcpy(ret, buffer);

	return ret;
}

FILE *prompt_user_and_open_file(void)
{
	char *file_name = NULL;
	FILE *file_pointer = NULL;

	do {
		file_name = readline("Enter a filename to parse: ");
	} while (file_name == NULL || !strlen(file_name));

	file_pointer = fopen(file_name, "r");
	free(file_name);

	if (!file_pointer) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	return file_pointer;
}
