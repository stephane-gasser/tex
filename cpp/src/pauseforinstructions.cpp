#include "pauseforinstructions.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void check_interrupt(void)
{
	if (interrupt)
		pauseforinstructions();
}

void pauseforinstructions(void)
{
	if (OKtointerrupt)
	{
		interaction = error_stop_mode;
		if (selector == log_only || selector == no_print)
			selector++;
		deletionsallowed = false;
		error("Interruption", "You rang?\nTry to insert some instructions for me (e.g.,`I\\showlists'),\nunless you just want to quit by typing `X'.");
		deletionsallowed = true;
		interrupt = 0;
	}
}
