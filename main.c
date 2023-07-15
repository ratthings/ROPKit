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

#include "file_io.h"
#include "memory_managment.h"

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
