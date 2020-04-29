#include "promptfilename.h"
#include "printnl.h"
#include "print.h"
#include "printfilename.h"
#include "showcontext.h"
#include "fatalerror.h"
#include "terminput.h"
#include "beginname.h"
#include "morename.h"
#include "endname.h"
#include "packfilename.h"
#include <iostream>

void promptfilename(strnumber s, strnumber e)
{
	if (interaction == 2)
		if (s == 786) //input file name
		{
			if (interaction == 3)
				printnl(262); //! 
			print(787); //I can't find file `
		}
		else
		{
			if (interaction == 3)
				printnl(262); //! 
			print(788); //I can't write on file `
		};
	printfilename(curname, curarea, curext);
	print(789); //'.
	if (e == 790) //.tex
		showcontext();
	printnl(791); //Please type another 
	print(s);
	if (interaction < 2)
		fatalerror(792); //*** (job aborted, file error in nonstop mode)
	std::cin.clear();
	print(568); //: 
	terminput();
	beginname();
	auto k = First;
	while (buffer[k] == ' '  && k < last)
		k++;
	while (true)
	{
		if (k == last)
			break;
		if (!morename(buffer[k]))
			break;
		k++;
	}
	endname();
	if (curext == 338) //
		curext = e;
	packfilename(curname, curarea, curext);
}
