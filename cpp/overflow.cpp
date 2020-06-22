#include "overflow.h"
#include "normalizeselector.h"
#include "printchar.h"
#include "printnl.h"
#include "print.h"
#include "print.h"
#include "printint.h"
#include "error.h"
#include "jumpout.h"
#include "texte.h"

void str_room(int n) //make sure that the pool hasn't overflowed
{
  if (poolptr+n > poolsize)
	  overflow("pool size", poolsize-initpoolptr); 
}

void overflow(const std::string &s, int n)
{
	normalizeselector();
	printnl("! "); 
	print("TeX capacity exceeded, sorry [");
	print(s);
	printchar('=');
	printint(n);
	printchar(']');
	helpptr = 2;
	helpline[1] = "If you really absolutely need more capacity,";
	helpline[0] = "you can ask a wizard to enlarge me.";
	if (interaction == error_stop_mode)
		interaction = scroll_mode;
	if (logopened)
		error();
	history = fatal_error_stop;
	jumpout();
}

void check_full_save_stack(void)
{
	if (saveptr > maxsavestack)
	{
		maxsavestack = saveptr; 
		if (maxsavestack> savesize-6) 
			overflow("save size",savesize);
	}
}

