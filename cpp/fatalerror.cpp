#include "fatalerror.h"
#include "normalizeselector.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "jumpout.h"
#include "texte.h"

void fatalerror(const std::string &s)
{
	normalizeselector();
	printnl("! ");
	print("Emergency stop");
	helpptr = 1;
	helpline[0] = txt(s);
	if (interaction == error_stop_mode)
		interaction = scroll_mode;
	if (logopened)
		error();
	history = fatal_error_stop;
	jumpout();
}
