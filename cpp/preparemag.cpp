#include "preparemag.h"
#include "printnl.h"
#include "print.h"
#include "printint.h"
#include "interror.h"
#include "geqworddefine.h"

void preparemag(void)
{
	if (magset > 0 && int_par(mag_code) != magset)
	{
		printnl(262); //! 
		print(547); //Incompatible magnification (
		printint(int_par(mag_code));
		print(548); //);
		printnl(549); // the previous value will be retained
		helpptr = 2;
		helpline[1] = 550; //I can handle only one magnification ratio per job. So I've
		helpline[0] = 551; //reverted to the magnification you used earlier on this run.
		interror(magset);
		geqworddefine(int_base+mag_code, magset);
	}
	if (int_par(mag_code) <= 0 || int_par(mag_code) > 0x80'00)
	{
		printnl(262); //! 
		print(552); //Illegal magnification has been changed to 1000
		helpptr = 1;
		helpline[0] = 553; //The magnification ratio must be between 1 and 0x80'00.
		interror(int_par(mag_code));
		geqworddefine(int_base+mag_code, 1000);
	}
	magset = int_par(mag_code);
}
