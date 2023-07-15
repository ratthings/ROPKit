/**
 * File: file_io.h
 *
 * Description:
 * Contains declarations for file I/O functions. The functions include
 * 'get_next_line' that reads a line from a file and 'prompt_user_and_open_file'
 * that prompts the user to enter a filename and open the file for reading.
 * The operations in these functions are safe, with proper error checking
 * and handling implemented.
 *
 * Author: snocra5h@icloud.com
 * Date: July 15, 2023
 */

#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define MAX_BUFFER 100

/**
 * get_next_line() - Read a line from a file
 * @fp: Pointer to the file
 *
 * This function reads a line from the provided file and returns a pointer to a
 * heap-allocated string containing the line. The string does not include the
 * newline character at the end of the line. If there are no more lines in the
 * file, or if an error occurs, it returns NULL.
 *
 * The caller is responsible for freeing the string after use.
 *
 * This function handles any errors that occur during reading or allocation by
 * printing an error message, closing the file, and terminating the program.
 *
 * Return: Pointer to the line, or NULL on end of file or error.
 */
char *get_next_line(FILE *fp);

/**
 * prompt_user_and_open_file() - Prompt the user for a filename and open the
 * file
 *
 * This function prompts the user to enter a filename using the readline
 * function, which allows the user to edit the filename and scroll through
 * previous filenames using the arrow keys. If the user doesn't enter any
 * filename, it re-prompts them until they do.
 *
 * After obtaining a filename, this function attempts to open the file in read
 * mode. If the file can't be opened, it prints an error message and terminates
 * the program.
 *
 * This function handles any errors that occur during prompting or opening the
 * file by printing an error message and terminating the program.
 *
 * Return: Pointer to the opened file.
 */
FILE *prompt_user_and_open_file(void);

#endif // FILE_IO_H
