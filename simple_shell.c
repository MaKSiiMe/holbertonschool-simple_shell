#include "shell.h"

/**
 * call_non_interactive_mode - function executing shell in non interective mode
 * Return: 0 if success execution
 *
 */

int call_non_interactive_mode(void)
{
	int ret = 0, nb_args = 0;
	ssize_t read_chars = 0;
	char *cmd_line;
	size_t len_cmd_line;
	char **args = NULL;

	while (read_chars != -1)
	{
		read_chars = getline(&cmd_line, &len_cmd_line, stdin);
		if (read_chars == EOF)
		{
			free(cmd_line);
			return (0);
		}
		nb_args = parse_cmd_line(cmd_line, &args);

		if (nb_args >= 2)
			synchronus_child_execution(args);

		len_cmd_line = 0;
		free(cmd_line);
		args = NULL;
	}
	free(cmd_line);

	return (ret);
}

/**
 * call_interactive_mode - function executing shell in interective mode
 *
 * Return: 0 if success execution
 */

int call_interactive_mode(void)
{
	int ret = 0, run = 1, nb_args = 0, i = 0;
	ssize_t read_chars = 0;
	char *cmd_line = NULL;
	size_t len_cmd_line = 0;
	char **args = NULL;

	while (run)
	{
		printf("($) ");
		fflush(stdin);
		args = NULL;
		read_chars = getline(&cmd_line, &len_cmd_line, stdin);
		if (read_chars == EOF)
		{
			free(cmd_line);
			run = 0;
			printf("\n");
			continue;
		}
		len_cmd_line = 0;
		if (strncmp(cmd_line, "exit", 4) == 0)
			shell_exit(cmd_line);

		if (strncmp(cmd_line, "env", 3) == 0)
		{
			print_env();
			continue;
		}
		if (cmd_line[0] == '\n')
			continue;

		nb_args = parse_cmd_line(cmd_line, &args);
		if (nb_args >= 2)
			synchronus_child_execution(args);
	}
	for (i = nb_args - 1; i >= 0; i--)
		free(args[i]);
	free(args);
	return (ret);
}
