#include "extrarightbrace.h"
#include "impression.h"
#include "erreur.h"
#include "alignement.h"
#include "sauvegarde.h"

void extrarightbrace(void)
{
	switch (curgroup)
	{
		case semi_simple_group: 
			error("Extra }, or forgotten "+esc("endgroup"), "I've deleted a group-closing symbol because it seems to be\nspurious, as in `$x}$'. But perhaps the } is legitimate and\nyou forgot something else, as in `\\hbox{$x}'. In such cases\nthe way to recover is to insert both the forgotten and the\ndeleted material, e.g., by typing `I$}'.");
			break;
		case math_shift_group: 
			error("Extra }, or forgotten $", "I've deleted a group-closing symbol because it seems to be\nspurious, as in `$x}$'. But perhaps the } is legitimate and\nyou forgot something else, as in `\\hbox{$x}'. In such cases\nthe way to recover is to insert both the forgotten and the\ndeleted material, e.g., by typing `I$}'.");
			break;
		case math_left_group: 
			error("Extra }, or forgotten "+esc("right"), "I've deleted a group-closing symbol because it seems to be\nspurious, as in `$x}$'. But perhaps the } is legitimate and\nyou forgot something else, as in `\\hbox{$x}'. In such cases\nthe way to recover is to insert both the forgotten and the\ndeleted material, e.g., by typing `I$}'.");
	}
	alignstate++;
}

