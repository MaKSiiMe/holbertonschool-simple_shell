#include "main.h"
/**
 *
 *
 *
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
