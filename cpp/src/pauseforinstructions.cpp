#include "pauseforinstructions.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void check_interrupt(void)
{
	if (interrupt)
		pauseforinstructions();
}

static void erreurPauseforinstructions(void)
{
	print_err("Interruption");
	helpptr = 3;
	helpline[2] = "You rang?";
	helpline[1] = "Try to insert some instructions for me (e.g.,`I\\showlists'),";
	helpline[0] = "unless you just want to quit by typing `X'.";
	deletionsallowed = false;
	error();
	deletionsallowed = true;
}

void pauseforinstructions(void)
{
	if (OKtointerrupt)
	{
		interaction = error_stop_mode;
		if (selector == log_only || selector == no_print)
			selector++;
		erreurPauseforinstructions();
		interrupt = 0;
	}
}
