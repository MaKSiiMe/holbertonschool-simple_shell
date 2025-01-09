#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int synchronus_child_execution(char *args[], int cmd_num);
char *my_strdup(const char *copy_str);
int parse_cmd_line(char *cmd_line, char ***ret);
void free_find_in_path(char *path_copy, char *full_path);
char *find_in_path(char *command);
int shell_exit(char *cmd_line, int cmd_num);
void print_env(void);
char *my_getenv(char *_env);
void print_error_msg(const char *message, const char *exec_name, int cmd_num);
void free_args(char **args);
int call_non_interactive_mode(void);
int call_interactive_mode(void);
void free_find_in_path(char *path_copy, char *full_path);
char *find_in_path(char *command);

#endif /* SHELL_H */
