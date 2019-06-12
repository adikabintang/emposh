#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *emposh_read_line()
{
        char *line = NULL;
        size_t bufsize = 0;
        getline(&line, &bufsize, stdin);
        return line;
}

char **emposh_split_line(char *line)
{
        int buffersize = EMPOSH_TOKEN_BUFSIZE;
        char *word;
        char **each_word = malloc(buffersize * sizeof(char *));
        CHECK_MALLOC_RETURN(each_word);
        int index = 0;
        
        word = strtok(line, " \t");
        while (word != NULL) {
                each_word[index++] = word;
                
                if (index >= buffersize) {
                        buffersize += EMPOSH_TOKEN_BUFSIZE;
                        each_word = realloc(each_word, 
                                buffersize * sizeof(char *));
                        CHECK_MALLOC_RETURN(each_word);
                }

                word = strtok(NULL, " \t");
        }
        
        each_word[index] = NULL;

        return each_word;
}

void emposh_loop()
{
        char *line;
        char **args;
        int status;
        int args_len = 0;

        do
        {
                printf("> ");
                line = emposh_read_line();
                args = emposh_split_line(line);
                
                args_len = 0;
                line = args[args_len];
                while (line != NULL) {
                        printf("-> %s\n", line);
                        line = args[++args_len];
                }
                printf("args_len: %d\n", args_len);
                // parse
                // run
                status = 0;
                
                free(line);
                free(args);
        } while (status);
}