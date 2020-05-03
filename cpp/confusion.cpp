#include "confusion.h"
#include "normalizeselector.h"
#include "printnl.h"
#include "print.h"
#include "printchar.h"
#include "error.h"
#include "jumpout.h"

void confusion(strnumber s)
{
	normalizeselector();
	if (history < error_message_issued)
	{
		printnl(262); //! 
		print(291); //This can't happen (
		print(s);
		printchar(')');
		helpptr = 1;
		helpline[0] = 292; //I'm broken. Please show this to someone who can fix can fix
	}
	else
	{
		printnl(262); //! 
		print(293); //I can't go on meeting you like this
		helpptr = 2;
		helpline[1] = 294; //One of your faux pas seems to have wounded me deeply...
		helpline[0] = 295; //in fact, I'm barely conscious. Please fix it and try again.
	}
	if (interaction == error_stop_mode)
		interaction = scroll_mode;
	if (logopened)
		error();
	history = fatal_error_stop;
	jumpout();
}
