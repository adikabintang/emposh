#include "util.h"
#include <stdlib.h>
#include <stdio.h>

char *emposh_read_line()
{
        int bufsize = EMPOSH_RL_BUFSIZE;
        int position = 0;
        char *buffer = malloc(sizeof(char) * bufsize);
        int c;

        if (!buffer) {
                fprintf(stderr, "emposh: cannot allocate buffer\n");
                exit(EXIT_FAILURE);
        }

        while (1) {
                c = getchar();

                if (c == EOF || c == '\n') {
                        return buffer;
                } else {
                        if (position >= bufsize) {
                                bufsize += EMPOSH_RL_BUFSIZE;
                                buffer = realloc(buffer, bufsize);
                        }

                        buffer[position++] = c;
                }
        }
}

void emposh_loop()
{
        char *line;
        char **args;
        int status;

        do
        {
                printf("> ");
                line = emposh_read_line();
                printf("line: %s\n", line);
                // parse
                // run
                status = 0;
                free (line);
        } while (status);
}