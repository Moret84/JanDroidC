#pragma once
#include <jandroid.h>
#define NBCOMMANDS 1

typedef struct Command Command;
struct Command
{
	char *name;
	void (*func)(Motor*);
};

Command* initCommands();
