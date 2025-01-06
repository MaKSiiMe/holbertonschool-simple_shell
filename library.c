#include "main.h"

/**
 *
 *
 */

void shell_exit(char *cmd_line)
{
	char **args = NULL;
	int nb_args = 0, code = 0;
	char *end = NULL;

	printf("SHELL_EXIT\n");

	nb_args = parse_cmd_line(cmd_line, &args);

	printf("Look %d\n", nb_args);
	printf("args[0] = %p\n", args[0]);
	if (nb_args == 2)
	{
		exit(0);
	}
	else if (nb_args == 3)
	{
		code = strtol(args[1], &end, 10);
		if (*end != '\0')
		{
			print_error_message("Error during conversion");
		}
		else
			exit(code);
	}
	else
		print_error_message("Exit faillure");



}

/**
 *
 *
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
 *
 *
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


