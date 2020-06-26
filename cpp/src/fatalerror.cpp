#include "fatalerror.h"
#include "normalizeselector.h"
#include "impression.h"
#include "error.h"
#include "jumpout.h"
#include "texte.h"

void fatalerror(const std::string &s)
{
	normalizeselector();
	print_err("Emergency stop");
	helpptr = 1;
	helpline[0] = s;
	if (interaction == error_stop_mode)
		interaction = scroll_mode;
	if (logopened)
		error();
	history = fatal_error_stop;
	jumpout();
}
