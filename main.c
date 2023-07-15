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
#include <stdlib.h> // strtol
#include <errno.h> // strtol
#include <limits.h> // strtol

#include "file_io.h"
#include "memory_managment.h"

// TODO: Need to get the -r value the user passed to rp++ for example if the
// user supplied the value 8 then we would need allocate 8
//       elements to some arrary of strings for each opcode.

// TODO: Need to make a linked list of stucts that contain the opcodes we want
// to parse.

// Example of a simple instruction: 0x11a3: add  [rbp-0x3D], ebx ; nop word [rax+rax+0x00000000] ; ret ; (1 found)
// Notice that all instructions end with (n found) meaning the number of
// identical strings.

// Example of a simple instruction: 0x11a3: add  [rbp-0x3D], ebx ; nop word [rax+rax+0x00000000] ; ret ; (1 found)
typedef struct Gadget {
	unsigned long address;
	char **opcodes;
	char **full_gadget;
} Gadget;

typedef struct Node {
	struct Gadget gadget;
	struct Node *next;
} Node;

unsigned long get_gadget_address(const char *gadget);

int main(void)
{
	FILE *fp = NULL;
	char *line = NULL;
	Node *head = NULL;
	int status_flag = EXIT_SUCCESS;

	fp = prompt_user_and_open_file();
	// 0x11a3: add  [rbp-0x3D], ebx ; nop word [rax+rax+0x00000000] ; ret ; (1 found)
	line = get_next_line(fp);
	puts(line);

	head = MALLOC(Node);
	if (head == NULL) {
		perror("MALLOC()");
		status_flag = EXIT_FAILURE;
	}
	head->next = NULL;
	head->gadget.full_gadget = head->gadget.opcodes = NULL;

	head->gadget.full_gadget = &line;

	free(*(head->gadget.full_gadget));
	*(head->gadget.full_gadget) = NULL;

	head->next = NULL;
	free(head);
	head = NULL;


	if (fp != NULL) // this will never be null
		fclose(fp);

	return status_flag;
}

unsigned long get_gadget_address(const char *gadget)
{
	int base;
	char *endptr, *str;
	long val;

	return 0;
}
