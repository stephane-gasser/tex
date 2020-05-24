#include "preparemag.h"
#include "printnl.h"
#include "print.h"
#include "printint.h"
#include "interror.h"
#include "geqworddefine.h"
#include "texte.h"

void preparemag(void)
{
	if (magset > 0 && int_par(mag_code) != magset)
	{
		printnl("! ");
		print("Incompatible magnification (");
		printint(int_par(mag_code));
		print(");");
		printnl(" the previous value will be retained");
		helpptr = 2;
		helpline[1] = "I can handle only one magnification ratio per job. So I've";
		helpline[0] = "reverted to the magnification you used earlier on this run.";
		interror(magset);
		geqworddefine(int_base+mag_code, magset);
	}
	if (int_par(mag_code) <= 0 || int_par(mag_code) > 0x80'00)
	{
		printnl("! ");
		print("Illegal magnification has been changed to 1000");
		helpptr = 1;
		helpline[0] = "The magnification ratio must be between 1 and 0x80'00.";
		interror(int_par(mag_code));
		geqworddefine(int_base+mag_code, 1000);
	}
	magset = int_par(mag_code);
}
