#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include "libft/libft.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Step 1: Open the file for writing (this will create or truncate the file)
    int fd = open("ss", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    // Step 2: Duplicate fd to stdout (fd 1)
    dup2(fd, STDOUT_FILENO);

    // Close the original file descriptor as it's no longer needed
    close(fd);

    // Step 3: Execute the "ls" command
    // This will write the output to "ss" instead of the terminal
    execlp("ls", "ls", NULL);

    // If execlp fails, print an error and exit
    perror("execlp");
    return 1;
}

