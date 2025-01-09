#include "shell.h"

/**
 * shell_exit - function implement the exit built-in
 * @cmd_line: command that was entered by the user and its arguments
 * @cmd_num: Command line number
 * Return: Exit status code
 */
int shell_exit(char *cmd_line, int cmd_num)
{
	char **args = NULL;
	int nb_args = 0, code = 0;
	char *end = NULL;

	nb_args = parse_cmd_line(cmd_line, &args);

	if (nb_args == 2)
	{
		free(cmd_line);
		free_args(args);
		exit(0);
	}
	if (nb_args > 3)
	{
		print_error_msg("Too many arguments", "exit", cmd_num);
		free_args(args);
		return (2);
	}
	if (args[1] == NULL)
	{
		print_error_msg("Illegal number", "exit", cmd_num);
		free_args(args);
		return (2);
	}
	code = strtol(args[1], &end, 10);
	if (*end != '\0')
	{
		print_error_msg("Illegal number", "exit", cmd_num);
		free_args(args);
		return (2);
	}
	free(cmd_line);
	free_args(args);
	exit(code);
}

/**
 *  print_env - function display the environment of the current process
 *  Return : Void
 */

void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * my_getenv - function get the value of an environment variable
 * @_env: name the variable environement that gives its value
 * Return: the value environment variable if found, otherwise NULL
 */

char *my_getenv(char *_env)
{
	int i = 0, len_env = 0;
	char *buf = NULL;

	while (_env[len_env] != '\0')
		len_env++;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], _env, len_env) == 0 && environ[i][len_env] == '=')
		{
			buf = strdup(environ[i] + len_env + 1);
			return (buf);
		}
	}
	return (NULL);
}

/**
 * print_error_msg - Prints an error message
 * @message: The error message to print
 * @exec_name: Name of the executable
 * @cmd_num: Command line number
 * Return : Void
 */

void print_error_msg(const char *message, const char *exec_name, int cmd_num)
{
	fprintf(stderr, "./hsh: %d: %s: %s\n", cmd_num, exec_name, message);
}

/**
 * free_args - function free args
 * @args : number arguments
 *
 */

void free_args(char **args)
{
	int i = 0;

	if (args)
	{
		while (args[i])
		{
			free(args[i]);
			args[i] = NULL;
			i++;
		}
		free(args);
		args = NULL;
	}
}
