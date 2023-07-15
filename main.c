// clang-format off
/*** ROPKit
 * 
 *   ██████  ███▄    █  ▒█████   █     █░ ▄████▄   ██▀███   ▄▄▄        ██████  ██░ ██
 * ▒██    ▒  ██ ▀█   █ ▒██▒  ██▒▓█░ █ ░█░▒██▀ ▀█  ▓██ ▒ ██▒▒████▄    ▒██    ▒ ▓██░ ██▒
 * ░ ▓██▄   ▓██  ▀█ ██▒▒██░  ██▒▒█░ █ ░█ ▒▓█    ▄ ▓██ ░▄█ ▒▒██  ▀█▄  ░ ▓██▄   ▒██▀▀██░
 *   ▒   ██▒▓██▒  ▐▌██▒▒██   ██░░█░ █ ░█ ▒▓▓▄ ▄██▒▒██▀▀█▄  ░██▄▄▄▄██   ▒   ██▒░▓█ ░██
 * ▒██████▒▒▒██░   ▓██░░ ████▓▒░░░██▒██▓ ▒ ▓███▀ ░░██▓ ▒██▒ ▓█   ▓██▒▒██████▒▒░▓█▒░██▓
 * ▒ ▒▓▒ ▒ ░░ ▒░   ▒ ▒ ░ ▒░▒░▒░ ░ ▓░▒ ▒  ░ ░▒ ▒  ░░ ▒▓ ░▒▓░ ▒▒   ▓▒█░▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒
 * ░ ░▒  ░ ░░ ░░   ░ ▒░  ░ ▒ ▒░   ▒ ░ ░    ░  ▒     ░▒ ░ ▒░  ▒   ▒▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░
 * ░  ░  ░     ░   ░ ░ ░ ░ ░ ▒    ░   ░  ░          ░░   ░   ░   ▒   ░  ░  ░   ░  ░░ ░
 *       ░           ░     ░ ░      ░    ░ ░         ░           ░  ░      ░   ░  ░  ░
 *                                   Written by: snowcra5h@icloud.com (snowcra5h) 2023
 *
 * This program parses Return Oriented Programming (ROP) gadgets from rp++ output,
 * and makes them quickly searchable. This allows for efficient exploration and 
 * utilization of ROP gadgets in. The tool aims to improve the speed and experience 
 * of working with ROP gadgets by providing a user-friendly interface.
 * 
 * Future enhancements include adding a GUI for an even more streamlined user experience.
 */
// clang-format on

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// clang-format off
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on

#include "memory_managment.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define MAX_BUFFER 100

FILE *prompt_user_and_open_file(void);
char *get_next_line(FILE *fp);

// TODO: Need to get the -r value the user passed to rp++ for example if the
// user supplied the value 8 then we would need allocate 8
//       elements to some arrary of strings for each opcode.

// TODO: Need to make a linked list of stucts that contain the opcodes we want
// to parse.

// Example of a simple instruction: 0x11a4: pop rbp ; ret ; (1 found)
// Notice that all instructions end with (n found) meaning the number of
// identical strings.

// Example of a simple instruction: 0x11a4: pop rbp ; ret ; (1 found)
#define MAX_ADDRESS 18
typedef struct Gadget {
  unsigned long address;
  char **opcodes;
  char *full_gadget;
} Gadget;

typedef struct Node {
  struct Gadget gadget;
  struct Node *next;
} Node;

int main(void) {
  FILE *fp = NULL;
  char *line = NULL;

  fp = prompt_user_and_open_file();

  while ((line = get_next_line(fp)) != NULL) {
    puts(line);
    free(line);
  }

  if (fp != NULL)
    fclose(fp);

  return 0;
}

/**
 * This function will not return if an error occurs.
 * When it encounters an EOF it will return NULL.
 *
 * The caller MUST free the returned char *
 */
char *get_next_line(FILE *fp) {
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

FILE *prompt_user_and_open_file(void) {
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
