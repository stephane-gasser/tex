#include "confusion.h"
#include "normalizeselector.h"
#include "printnl.h"
#include "print.h"
#include "printchar.h"
#include "error.h"
#include "jumpout.h"
#include "texte.h"

void confusion(const std::string &s)
{
	normalizeselector();
	if (history < error_message_issued)
	{
		printnl("! ");
		print("This can't happen (");
		print(s);
		printchar(')');
		helpptr = 1;
		helpline[0] = txt("I'm broken. Please show this to someone who can fix can fix");
	}
	else
	{
		printnl("! ");
		print("I can't go on meeting you like this");
		helpptr = 2;
		helpline[1] = txt("One of your faux pas seems to have wounded me deeply...");
		helpline[0] = txt("in fact, I'm barely conscious. Please fix it and try again.");
	}
	if (interaction == error_stop_mode)
		interaction = scroll_mode;
	if (logopened)
		error();
	history = fatal_error_stop;
	jumpout();
}
