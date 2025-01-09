#include "shell.h"

/**
 * free_find_in_path - function to free memory allocated in find_in_path
 * @path_copy: pointer to the duplicated PATH string
 * @full_path: pointer to the full path of the command
 */
void free_find_in_path(char *path_copy, char *full_path)
{
	if (path_copy)
		free(path_copy);
	if (full_path)
		free(full_path);
}

/**
 * find_in_path - function search for a command in the PATH
 * @command: pointer to the name of the command to search
 * Return: Full path of the command otherwise NULL
 */
char *find_in_path(char *command)
{
	char *path = NULL, *path_copy = NULL, *dir = NULL, *full_path = NULL;

	if (!command || strlen(command) == 0)
		return (NULL);

	if (strchr(command, '/'))
		return (NULL);

	path = my_getenv("PATH");
	if (!path || strlen(path) == 0)
		return (NULL);

	path_copy = strdup(path);
	free(path);
	if (!path_copy)
	{	perror("strdup");
		return (NULL);
	}
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{	full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			free_find_in_path(path_copy, NULL);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
