#include <Command.h>

Command* initCommands()
{
	Command *commands = malloc(NBCOMMANDS * sizeof(Command));
	commands[0].name = "forward";
	commands[0].func = &forward;

	return commands;
}
