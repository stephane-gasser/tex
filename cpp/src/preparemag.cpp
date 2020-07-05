#include "preparemag.h"
#include "impression.h"
#include "erreur.h"
#include "geqworddefine.h"
#include "texte.h"

static void erreurPreparemag1(void)
{
	print_err("Incompatible magnification ("+std::to_string(mag())+");\r the previous value will be retained");
	helpptr = 2;
	helpline[1] = "I can handle only one magnification ratio per job. So I've";
	helpline[0] = "reverted to the magnification you used earlier on this run.";
	interror(magset);
}

static void erreurPreparemag2(void)
{
	print_err("Illegal magnification has been changed to 1000");
	helpptr = 1;
	helpline[0] = "The magnification ratio must be between 1 and 0x80'00.";
	interror(mag());
}

void preparemag(void)
{
	if (magset > 0 && mag() != magset)
	{
		erreurPreparemag1();
		geqworddefine(int_base+mag_code, magset);
	}
	if (mag() <= 0 || mag() > 0x80'00)
	{
		erreurPreparemag2();
		geqworddefine(int_base+mag_code, 1000);
	}
	magset = mag();
}
