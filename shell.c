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
	int status;
	pid_t pid;
	char **_env = environ;
	printf("START SYNCH...\n");
	printf("args[0] = %s\n", args[0]);
	if (access(args[0], F_OK) != -1)
	{
		printf("file exists\n");

		if (access(args[0], X_OK) != -1)
		{
			printf("file is executable\n");
			pid = fork();

			if (pid < 0)
			{
				print_error_message("Cannot create child process");
				return (1);
			}
			else if (pid == 0)
			{
				execve(args[0], args, _env);
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
	printf("END SYNCH...\n");

	return (ret);
}

/**
 *
 *
 */

char **parse_cmd_line(char *cmd_line)
{
	char *tmp;
	char **ret;
	int i = 0, size = 0;
	char *copy = strdup(cmd_line);

	printf("START PARSE...\n");
	tmp = strtok(copy, " ");

	while (tmp)
	{
		size++;
		tmp = strtok(NULL, " ");
	}

	ret = malloc(sizeof(char *) * (size + 1));

	if (!ret)
	{
		printf("Error in parse_cmd_line\n");
		free(tmp);
		exit(0);
	}
	tmp = NULL;

	tmp = strtok(cmd_line, " \r\n");

	while (tmp)
	{
		ret[i] = tmp;
		printf("ret[%d] = %s\n", i, tmp);
		i++;
		tmp = strtok(NULL, " \r\n");
	}
	free(tmp);
	ret[++i] = NULL;
	printf("END PARSE...\n");

	return (ret);
}

/**
 *
 *
 */

int call_non_interactive_mode(void)
{
	int ret = 0;
	ssize_t read_chars = 0;
	char *cmd_line;
	size_t len_cmd_line;

	while (read_chars != -1)
	{
		printf("START WHILE...\n");
		read_chars = getline(&cmd_line, &len_cmd_line, stdin);
		printf("getline\n");
		if (read_chars == EOF)
		{
			free(cmd_line);
			return (0);
		}
		printf("%s", cmd_line);
		synchronus_child_execution(parse_cmd_line(cmd_line));
		len_cmd_line = 0;
		free(cmd_line);
		printf("END WHILE...\n");
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
	int ret = 0;



	return (ret);
}
