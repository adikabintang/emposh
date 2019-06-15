#include "util.h"
#include "builtin_commands.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
        
        word = strtok(line, " \t\n");
        while (word != NULL) {
                each_word[index++] = word;
                
                if (index >= buffersize) {
                        buffersize += EMPOSH_TOKEN_BUFSIZE;
                        each_word = realloc(each_word, 
                                buffersize * sizeof(char *));
                        CHECK_MALLOC_RETURN(each_word);
                }

                word = strtok(NULL, " \t\n");
        }
        
        each_word[index] = NULL;

        return each_word;
}

int emposh_launch(char **args)
{
        pid_t pid, wpid;
        int status;

        pid = fork();
        if (pid == 0) {
                // this is child process
                if (execvp(args[0], args) == -1) {
                        perror("emposh");
                }
                exit(EXIT_FAILURE);
        } else if (pid < 0) {
                // error forking
                perror("emposh");
        } else {
                // this is parent process
                do {
                        wpid = waitpid(pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }

        return 1;
}

int emposh_execute(char **args)
{
        int i;

        if (args[0] == NULL) {
                // An empty command was entered
                return 1;
        }

        for (i = 0; i < emposh_num_builtins(); i++) {
                if (strcmp(args[0], builtin_str[i]) == 0) {
                        return (*builtin_func[i])(args);
                }
        }

        return emposh_launch(args);
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
                status = emposh_execute(args);
                
                free(line);
                free(args);
        } while (status != 0);
}