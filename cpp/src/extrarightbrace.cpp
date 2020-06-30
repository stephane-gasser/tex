#include "extrarightbrace.h"
#include "impression.h"
#include "error.h"
#include "texte.h"

void extrarightbrace(void)
{
	switch (curgroup)
	{
		case semi_simple_group: 
			print_err("Extra }, or forgotten "+esc("endgroup"));
			break;
		case math_shift_group: 
			print_err("Extra }, or forgotten $");
			break;
		case math_left_group: 
			print_err("Extra }, or forgotten "+esc("right"));
	}
	helpptr = 5;
	helpline[4] = "I've deleted a group-closing symbol because it seems to be";
	helpline[3] = "spurious, as in `$x}$'. But perhaps the } is legitimate and";
	helpline[2] = "you forgot something else, as in `\\hbox{$x}'. In such cases";
	helpline[1] = "the way to recover is to insert both the forgotten and the";
	helpline[0] = "deleted material, e.g., by typing `I$}'.";
	error();
	alignstate++;
}

