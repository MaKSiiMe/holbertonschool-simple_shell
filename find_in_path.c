#include "shell.h"
/**
 * find_in_path - function search for a command in the PATH
 * @command: pointer to the name of the command to search
 * Return: Full path of the command otherwize 0
 */

char *find_in_path(char *command)
{
	char *path = NULL, *path_copy = NULL, *dir = NULL, *full_path = NULL;

	path = my_getenv("PATH");
	if (path == NULL || strlen(path) == 0)
	{
		print_error_message("Error: Invalid PATH environment variable");
		return (0);
	}
	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);

		if (full_path == NULL)
		{
			perror("malloc");
			free(path_copy);
			exit(EXIT_FAILURE);
		}
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, F_OK) != -1 && access(full_path, X_OK) != -1)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (0);
}
