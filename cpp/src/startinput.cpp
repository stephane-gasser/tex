#include "startinput.h"
#include "lecture.h"
#include "fichier.h"
#include "impression.h"
#include "equivalent.h"
#include "chaine.h"
#include <iostream>

constexpr char TEX_area[] = "TeXinputs:";

void startinput(void)
{
	scanfilename();
	if (curext == "")
		curext = ".tex";
	name = pack_cur_name();
	while (true)
	{
		beginfilereading();
		if (aopenin(cur_file(), name))
			break;
		if (curarea == "" && aopenin(cur_file(), packfilename(curname, TEX_area, curext)))
			break;
		endfilereading();
		name = promptfilename("input file name", ".tex");
	}
	if (jobname == "")
	{
		jobname = curname;
		openlogfile();
	}
	print(std::string(termoffset+name.size() > maxprintline-2 ? "\n" : termoffset > 0 || fileoffset > 0 ? " " : "")+"(");
	openparens++;
	print(name);
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
