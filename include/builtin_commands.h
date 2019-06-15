#ifndef _BUILTIN_COMMANDS_H
#define _BUILTIN_COMMANDS_H

int emposh_cd(char **args);
int emposh_help(char **args);
int emposh_exit(char **args);

extern char *builtin_str[];

extern int (*builtin_func[])(char **);

int emposh_num_builtins();

#endif