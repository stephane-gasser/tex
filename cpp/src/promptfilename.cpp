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
#include "texte.h"

void promptfilename(const std::string &s, const std::string &e)
{
	if (interaction == scroll_mode)
		if (s == "input file name")
		{
			printnl("! ");
			print("I can't find file `");
		}
		else
		{
			printnl("! ");
			print("I can't write on file `");
		};
	printfilename(curname, curarea, curext);
	print("'.");
	if (e == ".tex")
		showcontext();
	printnl("Please type another ");
	print(s);
	if (interaction < scroll_mode)
		fatalerror("*** (job aborted, file error in nonstop mode)");
	std::cin.clear();
	print(": ");
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
	if (curext == "")
		curext = e;
	pack_cur_name();
}
