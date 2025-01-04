#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

/**
 *
 *
 *
 *
 */

extern char **environ;

int call_interactive_mode(void);
int call_non_interactive_mode(void);
int synchronus_child_execution(char *args[]);
void print_error_message(char *message);
char **parse_cmd_line(char *cmd_line);







#endif
