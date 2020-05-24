#include "pauseforinstructions.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "texte.h"

void pauseforinstructions(void)
{
	if (OKtointerrupt)
	{
		interaction = error_stop_mode;
		if (selector == log_only || selector == no_print)
			selector++;
		printnl("! ");
		print("Interruption");
		helpptr = 3;
		helpline[2] = "You rang?";
		helpline[1] = "Try to insert some instructions for me (e.g.,`I\\showlists'),";
		helpline[0] = "unless you just want to quit by typing `X'.";
		deletionsallowed = false;
		error();
		deletionsallowed = true;
		interrupt = 0;
	}
}
