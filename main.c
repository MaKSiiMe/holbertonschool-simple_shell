#include "main.h"
/**
 *
 *
 *
 */

int main(int argc, char *argv[])
{
	int ret = 0;

	if (argc > 1)
	{
		call_non_interactive_mode(argc, argv);
	}
	else
	{
		call_interative_mode();
	}

	return (ret);
}
