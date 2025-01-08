#include "shell.h"

/**
 * synchronus_child_execution - create & execute a child. Wait for termination
 * @args: Array of arguments for the command to be executed
 * Return: Error code otherwise 0
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
				wait(&status);
		}
		else
		{
			print_error_message("file is not executable\n");
			return (0);
		}
	}
	else
	{
		print_error_message("file does not exist");
		return (0);
	}
	return (ret);
}
/**
 * parse_cmd_line - function parses a command line and transform an array args
 * @ret: pointer to an array that will receive the adress of the array of args
 * @cmd_line: String containing the command line to be parsed
 * Return: the number of arguments
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
	*ret = (char **)malloc(sizeof(char *) * size);
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
	free(copy);
	(*ret)[i] = NULL;
	return (size);
}
