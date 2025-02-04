#include "shell.h"
#include <signal.h>

/**
 * call_non_interactive_mode - function executing shell in non interective mode
 * Return: 0 if success execution
 */
int call_non_interactive_mode(void)
{
	int ret = 0, nb_args = 0, cmd_num = 0;
	ssize_t read_chars = 0;
	char *cmd_line = NULL;
	size_t len_cmd_line = 0;
	char **args = NULL;

	while (read_chars != -1)
	{
		read_chars = getline(&cmd_line, &len_cmd_line, stdin);
		cmd_num++;
		if (read_chars == EOF)
		{
			free(cmd_line);
			cmd_line = NULL;
			return (0);
		}
		if (strncmp(cmd_line, "exit", 4) == 0 &&
				(cmd_line[4] == '\n' || cmd_line[4] == ' ' || cmd_line[4] == '\0'))
		{
			ret = shell_exit(cmd_line, cmd_num);
			free(cmd_line);
			exit(ret);
		}
		if (strncmp(cmd_line, "env", 3) == 0)
		{
			print_env();
			continue;
		}
		if (cmd_line[0] == '\n')
			continue;

		nb_args = parse_cmd_line(cmd_line, &args);

		if (nb_args > 1)
			synchronus_child_execution(args, cmd_num);
		free_args(args);
		args = NULL;
	}
	free(cmd_line);
	return (ret);
}

/**
 * interruption_handling - function to handle CTRL+C
 * @sig: signal interruption number
 */
void interruption_handling(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		printf("$ ");
		fflush(stdout);
	}
}

/**
 * call_interactive_mode - function executing shell in interective mode
 * Return: 0 if success execution
 */
int call_interactive_mode(void)
{	int ret = 0, run = 1, nb_args = 0, cmd_num = 0;
	ssize_t read_chars = 0;
	char *cmd_line = NULL;
	size_t len_cmd_line = 0;
	char **args = NULL;

	signal(SIGINT, interruption_handling);
	while (run)
	{	printf("$ ");
		fflush(stdin);
		args = NULL;
		read_chars = getline(&cmd_line, &len_cmd_line, stdin);
		if (read_chars == -1)
		{	free(cmd_line);
			run = 0;
			printf("\n");
			exit(ret);
		}
		cmd_num++;
		if (strncmp(cmd_line, "exit", 4) == 0 &&
				(cmd_line[4] == '\n' || cmd_line[4] == ' ' || cmd_line[4] == '\0'))
		{	ret = shell_exit(cmd_line, cmd_num);
			free(cmd_line);
			exit(ret);
		}
		if (strncmp(cmd_line, "env", 3) == 0)
		{	print_env();
			continue;
		}
		if (cmd_line[0] == '\n')
			continue;
		nb_args = parse_cmd_line(cmd_line, &args);
		if (nb_args)
			ret = synchronus_child_execution(args, cmd_num);
		free_args(args);
		args = NULL;
		free(cmd_line);
		cmd_line = NULL;
		len_cmd_line = 0;
	}
	return (ret);
}
