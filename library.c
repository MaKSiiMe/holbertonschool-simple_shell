#include "shell.h"

/**
 * shell_exit - function implement the exit built-in
 * @cmd_line: command that was entered by the user and its arguments
 * @cmd_num: Command line number
 * Return: Void
 */

int shell_exit(char *cmd_line, int cmd_num)
{
	char **args = NULL;
	int nb_args = 0, code = 0, ret = 0;
	char *end = NULL, *tmp_msg = "Illegal number: ", *msg = NULL;

	nb_args = parse_cmd_line(cmd_line, &args, cmd_num);
	
	if (nb_args == 2)
	{
		exit(0);
	}
	if (args[1] != NULL)
	{
		code = strtol(args[1], &end, 10);
		if (*end != '\0')
		{
			msg = malloc(strlen(tmp_msg) + strlen(args[1]) + 2);
			strcpy(msg, tmp_msg);
			strcat(msg, args[1]);
			print_error_message(msg, "exit", cmd_num);
			free(msg);
			ret = 2;
		}
		else
			exit(code);
	}
	else
		ret = 2;
	
	for (int i = 0; i < nb_args; i++)
		free(args[i]);
	
	free(args);
	return (ret);
}

/**
 *  print_env - function display the environment of the current process
 *  Return: Void
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
	char *env_copy = NULL;

	while (_env[len_env] != '\0')
		len_env++;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], _env, len_env) == 0)
		{
			env_copy = strdup(environ[i]);
			buf = strtok(env_copy, "=");
			buf = strtok(NULL, "=");
			return (buf);
		}
	}
	return (buf);
}

/**
 * print_error_message - Prints an error message
 * @message: The error message to print
 * @exec_name: Name of the executable
 * @cmd_num: Command line number
 * Return : Void
 */

void print_error_message(char *message, char *exec_name, int cmd_num)
{
	fprintf(stderr, "./hsh: %d: %s: %s\n", cmd_num, exec_name, message);
}
