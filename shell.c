#include "main.h"

/**
 * print_error_message - Prints an error message
 * @message: The error message to print
 * Return : Void
 */

void print_error_message(char *message)
{
	printf("%s\n", message);
}

/**
 * synchronus_child_execution - create & execute a child. Wait for termination
 * @exec_file: Path to the executable file
 * Return : Error code otherwise 0
 */

int synchronus_child_execution(char *args[])
{
	int ret = 0;
	int status = 0;
	pid_t pid;
	char *tmp = NULL;
	char **_env = environ;

	tmp = find_in_path(args[0]);
	if (!tmp)
		tmp = args[0];

	
	if (access(tmp, F_OK) != -1)
	{

		if (access(tmp, X_OK) != -1)
		{
			pid = fork();

			if (pid < 0)
			{
				print_error_message("Cannot create child process");
				return (1);
			}
			else if (pid == 0)
			{
				execve(tmp, args, _env);
				exit(0);
			}
			else
			{
				wait(&status);
			}

		}
		else
		{
			print_error_message("file is not executable\n");
			exit(0);
		}

	}
	else
	{
		print_error_message("file does not exist");
		exit(0);
	}

	return (ret);
}

/**
 *
 *
 */

int parse_cmd_line(char *cmd_line, char ***ret)
{
	char *tmp = NULL;
	int i = 0, size = 0;
	char *copy = strdup(cmd_line);

	if ((*ret))
	{
		print_error_message("Error ret is not NULL");
		return (0);
	}

	if (!copy)
	{
		print_error_message("Error with strdup");
		return (0);
	}
	tmp = strtok(copy, " ");

	while (tmp)
	{
		size++;
		tmp = strtok(NULL, " ");
	}
	size++;

	*ret = (char**)malloc(sizeof(char *) * size);

	if (!(*ret))
	{
		printf("Error in parse_cmd_line\n");
		free(tmp);
		exit(0);
	}
	tmp = NULL;

	tmp = strtok(cmd_line, " \n");

	while (tmp)
	{
		(*ret)[i] = strdup(tmp);
		i++;
		tmp = strtok(NULL, " \n");
	}
	free(tmp);
	free(copy);
	(*ret)[++i] = NULL;


	return (size);
}

/**
 *
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
 *
 *
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
		}
		len_cmd_line = 0;
		
		if (strncmp(cmd_line, "exit", 4) == 0)
		{
			shell_exit(cmd_line);
		}
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
