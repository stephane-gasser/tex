#include "reportillegalcase.h"
#include "youcant.h"
#include "error.h"
#include "texte.h"

void reportillegalcase(void)
{
	youcant();
	helpptr = 4;
	helpline[3] = "Sorry, but I'm not programmed to handle this case;";
	helpline[2] = "I'll just pretend that you didn't ask for it.";
	helpline[1] = "If you're in the wrong mode, you might be able to";
	helpline[0] = "return to the right one by typing `I}' or `I$' or `I\\par'.";
	error();
}
