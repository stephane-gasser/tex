#include "youcant.h"
#include "printnl.h"
#include "print.h"
#include "printcmdchr.h"
#include "printmode.h"

void youcant(void)
{
	if (interaction == 3)
		printnl(262); //! 
	print(685); //You can't use `
	printcmdchr(curcmd, curchr);
	print(1019); //' in 
	printmode(mode);
}
