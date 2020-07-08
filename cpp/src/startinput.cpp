#include "startinput.h"
#include "lecture.h"
#include "packfilename.h"
#include "beginfilereading.h"
#include "fichier.h"
#include "endfilereading.h"
#include "promptfilename.h"
#include "openlogfile.h"
#include "impression.h"
#include "firmuptheline.h"
#include "amakenamestring.h"
#include "inputln.h"
#include <iostream>
#include "texte.h"

constexpr char TEX_area[] = "TeXinputs:";

void startinput(void)
{
	scanfilename();
	if (curext == "")
		curext = ".tex";
	pack_cur_name();
	while (true)
	{
		beginfilereading();
		if (aopenin(cur_file()))
			break;
		if (curarea == "")
		{
			packfilename(curname, TEX_area, curext);
			if (aopenin(cur_file()))
				break;
		}
		endfilereading();
		promptfilename("input file name", ".tex");
	}
	name = amakenamestring(cur_file());
	if (jobname == "")
	{
		jobname = curname;
		openlogfile();
	}
	print(std::string(termoffset+name.size() > maxprintline-2 ? "\n" : termoffset > 0 || fileoffset > 0 ? " " : "")+"(");
	openparens++;
	slowprint(name);
	std::cout << std::flush;
	state = new_line;
	if (name == strings.back())
	{
		flush_string();
		name = curname;
	}
	line = 1;
	if (inputln(cur_file(), false))
		firmuptheline();
	if (end_line_char_inactive())
		limit--;
	else
		buffer[limit] = end_line_char();
	First = limit+1;
	loc = start;
}
