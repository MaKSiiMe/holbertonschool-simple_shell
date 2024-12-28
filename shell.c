#include "main.h"
/**
 * print_error_message - Prints an error message
 * @message: The error message to print
 * Return : Void
 */

void print_error_message(char *message)
{
	printf("%s", message);
}

/**
 * synchronus_child_execution - create & execute a child. Wait for termination
 * @exec_file: Path to the executable file
 * Return : Error code otherwise 0
*/

int synchronus_child_execution(char *exec_file)
{
	int ret = 0;
	int status;
	pid_t pid = fork();

	if (pid < 0)
	{
		print_error_message("Cannot create child process");
		return (1);
	}
	else if (pid == 0)
	{
		execve(exec_file, NULL, NULL);
		exit (0);
	}
	else
	{
		wait(&status);
	}
	return (ret);
}

/**
 *
 *
 */

int call_non_interactive_mode(int argc, char *argv[])
{
	int ret = 0;



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
