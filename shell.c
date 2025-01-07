#include "shell.h"
/**
 * main - Main entry point of the program
 *
 * Return: 0 if success execution
 */

int main(void)
{
	int ret = 0;


	/*disable CTRL+C from here*/
	signal(SIGINT, SIG_IGN);

	/* check if the STDIN of the program is connected to the terminal*/
	if (isatty(STDIN_FILENO))
	{
		call_interactive_mode();
	}
	else
	{
		call_non_interactive_mode();
	}

	return (ret);
}
