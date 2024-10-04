#include "../incld/minishell.h"

#define BUFFER_SIZE 1024

// Function to read a line of input from stdin
char *readline_dyali() {
    char *buffer = NULL;
    int position = 0;
    int buffer_size = BUFFER_SIZE;
    char ch;

    // Allocate the initial memory for the buffer
    buffer = malloc(sizeof(char) * buffer_size);
    if (!buffer) {
        fprintf(stderr, "Allocation error\n");
        return NULL;
    }

    // Read characters one by one
	printf(COLOR_BOLD_RED "➜  minishell " COLOR_RESET);
    while (1) {
        ch = getchar();  // Get the next character from stdin

        // Check for end of input or new line
        if (ch == EOF || ch == '\n') {
            buffer[position] = '\0';  // Null-terminate the string
            return buffer;
        } else {
            buffer[position] = ch;
        }
        position++;

        // If the buffer is exceeded, reallocate memory
        if (position >= buffer_size) {
            buffer_size += BUFFER_SIZE;
            buffer = realloc(buffer, buffer_size);
            if (!buffer) {
                fprintf(stderr, "Reallocation error\n");
                return NULL;
            }
        }
    }
}