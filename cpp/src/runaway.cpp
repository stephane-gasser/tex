#include "runaway.h"
#include "impression.h"
#include "lecture.h"
#include "getnext.h"
#include "token.h"

void runaway(char status)
{
	if (status <= skipping)
		return;
	switch (status)
	{
		case defining:
			print("\rRunaway definition?\n"+tokenlist(&defRef, errorline-10));
			break;
		case matching:
			print("\rRunaway argument?\n"+tokenlist(&tempHead, errorline-10));
			break;
		case aligning:
			print("\rRunaway preamble?\n"+tokenlist(&holdHead, errorline-10));
			break;
		case absorbing:
			print("\rRunaway text?\n"+tokenlist(&defRef, errorline-10));
	}
}
