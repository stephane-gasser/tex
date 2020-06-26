#include "preparemag.h"
#include "impression.h"
#include "interror.h"
#include "geqworddefine.h"
#include "texte.h"

void preparemag(void)
{
	if (magset > 0 && mag() != magset)
	{
		print_err("Incompatible magnification ("+std::to_string(mag())+");");
		printnl(" the previous value will be retained");
		helpptr = 2;
		helpline[1] = "I can handle only one magnification ratio per job. So I've";
		helpline[0] = "reverted to the magnification you used earlier on this run.";
		interror(magset);
		geqworddefine(int_base+mag_code, magset);
	}
	if (mag() <= 0 || mag() > 0x80'00)
	{
		print_err("Illegal magnification has been changed to 1000");
		helpptr = 1;
		helpline[0] = "The magnification ratio must be between 1 and 0x80'00.";
		interror(mag());
		geqworddefine(int_base+mag_code, 1000);
	}
	magset = mag();
}
