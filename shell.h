#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

extern char **environ;

int call_interactive_mode(void);
int call_non_interactive_mode(void);
int synchronus_child_execution(char *args[], int cmd_num);
void print_error_message(char *message, char *exec_name, int cmd_num);
int parse_cmd_line(char *cmd_line, char ***ret, int cmd_num);
int shell_exit(char *cmd_line, int cmd_num);
void print_env(void);
char *my_getenv(char *_env);
char *find_in_path(char *command);
void interruption_handling(int sig);
void free_args(char **args);

#endif
