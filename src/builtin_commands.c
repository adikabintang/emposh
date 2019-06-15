#include "builtin_commands.h"
#include <stdio.h>
#include <unistd.h>

char *builtin_str[] = {
        "cd",
        "help",
        "exit"
};

int (*builtin_func[])(char **) = {
        &emposh_cd,
        &emposh_help,
        &emposh_exit
};

int emposh_num_builtins()
{
        return sizeof(builtin_str) / sizeof(char *);
}

int emposh_cd(char **args)
{
        if (args[1] == NULL) {
                fprintf(stderr, "emposh: expected argument to 'cd'\n");
        } else {
                if (chdir(args[1]) != 0) {
                        perror("emposh");
                }
        }
        return 1;
}

int emposh_help(char **args)
{
        int i;
        printf("Bintang's Emposh\n");
        printf("Credit to Stephen Brennan's Tutorial\n");
        printf("Type program names and arguments, and hit enter.\n");
        printf("The following are built in:\n");

        for (i = 0; i < emposh_num_builtins(); i++) {
                printf("\t%s\n", builtin_str[i]);
        }

        printf("Use 'man' command for more information\n");
        return 1;
}

int emposh_exit(char **args)
{
        return 0;
}