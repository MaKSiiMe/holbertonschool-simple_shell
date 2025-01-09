#include "shell.h"

/**
 * synchronus_child_execution - create & execute a child. Wait for termination
 * @args: Array of arguments for the command to be executed
 * @cmd_num: Command line number
 * Return: Error code otherwise 0
 */
int synchronus_child_execution(char *args[], int cmd_num)
{
	int ret = 0, ret_exec = 0, status = 0;
	pid_t pid;
	char *tmp = NULL;
	char **_env = environ;

	tmp = find_in_path(args[0]);
	if (!tmp)
		tmp = args[0];
	if (access(tmp, F_OK) != -1)
	{
		if (access(tmp, X_OK) != -1)
		{	pid = fork();
			if (pid < 0)
			{	print_error_message("Cannot create child process", args[0], cmd_num);
				return (1);
			}
			else if (pid == 0)
			{
				ret_exec = execve(tmp, args, _env);
				exit(ret_exec);
			}
			else
			{
				wait(&status);
				if (WIFEXITED(status))
					ret = WEXITSTATUS(status);
			}
		}
		else
		{
			print_error_message("Permission denied", args[0], cmd_num);
			return (126);
		}
	}
	else
	{
		print_error_message("not found", args[0], cmd_num);
		return (127);
	}
	return (ret);
}
/**
 *
 *
 *
 */

char *my_strdup(const char *copy_str)
{
	char *ret = NULL;
	size_t len = strlen(copy_str) + 1;

	if (!copy_str)
		return (NULL);
	ret = malloc(len);

	if (!ret)
		return (NULL);
	memcpy(ret, copy_str, len);
	return (ret);
}


/**
 * parse_cmd_line - function parses a command line and transform an array args
 * @ret: pointer to an array that will receive the adress of the array of args
 * @cmd_line: String containing the command line to be parsed
 * @cmd_num: Command line number
 * Return: the number of arguments
 */

int parse_cmd_line(char *cmd_line, char ***ret, int cmd_num)
{
	char *tmp = NULL;
	int i = 0, size = 0;
	char *copy = NULL;
	
	copy = strdup(cmd_line);
	
	printf("%p %s", cmd_line, cmd_line);

	if ((*ret))
	{
		print_error_message("Error ret is not NULL", "./hsh", cmd_num);
		free(copy);
		return (0);
	}
	if (!copy)
	{
		print_error_message("Error with strdup", "./hsh", cmd_num);
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
		free(copy);
		exit(0);
	}
	free(tmp);
	tmp = strtok(cmd_line, " \n");
	while (tmp)
	{
		(*ret)[i] = my_strdup(tmp);
		i++;
		tmp = strtok(NULL, " \n");
	
	}
	(*ret)[i] = NULL;

/*	for (i = 0; i < size - 1; i++)
		free((*ret)[i]);*/
	free(*ret);
	free(copy);
	free(tmp);
	return (size);
}
