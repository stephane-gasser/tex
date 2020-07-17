#include "promptfilename.h"
#include "impression.h"
#include "erreur.h"
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
		print_err(s == "input file name" ? "I can't find file `" : "I can't write on file `"+asFilename(curname, curarea, curext)+"'.");
	if (e == ".tex")
		print(showcontext());
	printnl("Please type another "+s);
	if (interaction < scroll_mode)
		fatalerror("*** (job aborted, file error in nonstop mode)", curalign);
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
