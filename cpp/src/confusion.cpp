#include "confusion.h"
#include "normalizeselector.h"
#include "impression.h"
#include "error.h"
#include "jumpout.h"
#include "texte.h"

void confusion(const std::string &s)
{
	normalizeselector();
	if (history < error_message_issued)
	{
		print_err("This can't happen ("+s+")");
		helpptr = 1;
		helpline[0] = "I'm broken. Please show this to someone who can fix can fix";
	}
	else
	{
		print_err("I can't go on meeting you like this");
		helpptr = 2;
		helpline[1] = "One of your faux pas seems to have wounded me deeply...";
		helpline[0] = "in fact, I'm barely conscious. Please fix it and try again.";
	}
	if (interaction == error_stop_mode)
		interaction = scroll_mode;
	if (logopened)
		error();
	history = fatal_error_stop;
	jumpout();
}
