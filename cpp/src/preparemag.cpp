#include "preparemag.h"
#include "impression.h"
#include "erreur.h"
#include "equivalent.h"

static int magset = 0;

void preparemag(void)
{
	if (magset > 0 && mag() != magset)
	{
		interror(magset, "Incompatible magnification ("+std::to_string(mag())+");\r the previous value will be retained", "I can handle only one magnification ratio per job. So I've\nreverted to the magnification you used earlier on this run.");
		word_define(4, &eqtb_int[mag_code], magset);
	}
	if (mag() <= 0 || mag() > 0x80'00)
	{
		interror(mag(), "Illegal magnification has been changed to 1000", "The magnification ratio must be between 1 and 0x80'00.");
		word_define(4, &eqtb_int[mag_code], 1000);
	}
	magset = mag();
}
