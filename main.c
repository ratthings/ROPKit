#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv)
{
    (void) argc; 
    (void) (argv);


    char *file_name = NULL; 
    
    file_name = readline("Enter a filename to parse: ");

    puts(file_name);

    if (file_name != NULL) {
        free(file_name);
        file_name = NULL;
    }

    return 0;
}