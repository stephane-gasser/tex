#include "runaway.h"
#include "impression.h"
#include "lecture.h"
#include "getnext.h"
#include "token.h"

void runaway(void)
{
	if (scannerstatus <= skipping)
		return;
	printnl("Runaway ");
	switch (scannerstatus)
	{
		case defining:
			print("definition?\n"+tokenlist(&defRef, errorline-10));
			break;
		case matching:
			print("argument?\n"+tokenlist(&tempHead, errorline-10));
			break;
		case aligning:
			print("preamble?\n"+tokenlist(&holdHead, errorline-10));
			break;
		case absorbing:
			print("text?\n"+tokenlist(&defRef, errorline-10));
	}
}
