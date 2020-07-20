#include "globals.h"
#include "initialize.h"
#include "initprim.h"
#include "getstringsstarted.h"
#include "fixdateandtime.h"
#include "impression.h"
#include "openfmtfile.h"
#include "initterminal.h"
#include "loadfmtfile.h"
#include "startinput.h"
#include "fichier.h"
#include "maincontrol.h"
#include "finalcleanup.h"
#include "closefilesandterminate.h"
#include <iostream>

int main()
{
	try
	{
		history = fatal_error_stop;
		if (readyalready != 314159)
		{
			bad = 0;
			if (halferrorline < 30 || halferrorline > errorline-15)
				bad = 1;
			if (maxprintline < 60)
				bad = 2;
			if (dvibufsize%8)
				bad = 3;
			if (1100 > mem_top)
				bad = 4;
			if (hash_prime > 2100)
				bad = 5;
			if (maxinopen >= 128)
				bad = 6;
			if (mem_top < 267)
				bad = 7;
			if (memmin != 0 || memmax != mem_top)
				bad = 10;
			if (memmin > 0 || memmax < mem_top)
				bad = 10;
			if (0 > 0 || 255 < 127)
				bad = 11;
			if (0 > 0 || empty_flag < 0x7F'FF)
				bad = 12;
			if (0 < 0 || 255 > empty_flag)
				bad = 13;
			if (memmin < 0 || memmax >= empty_flag || -0-memmin > 0x1'00'00)
				bad = 14;
			if (0 < 0 || fontmax > 255)
				bad = 15;
			if (fontmax > 256)
				bad = 16;
			if (savesize > empty_flag || maxstrings > empty_flag) 
				bad = 17;
			if (bufsize > empty_flag)
				bad = 18;
			if (255 < 255)
				bad = 19;
			if (6976 > empty_flag)
				bad = 21;
			if (20 > filenamesize)
				bad = 31;
			if (2*empty_flag < mem_top-memmin)
				bad = 41;
			if (bad > 0)
			{
				std::cout << "Ouch---my internal constants have been clobbered! ---case " << bad << std::endl;
				throw std::string();
			}
			Initialize();
			if (!getstringsstarted())
				throw std::string();
			initprim();
			//initstrptr = strptr;
			//initpoolptr = poolptr;
			fixdateandtime();
			readyalready = 314159;
		}
		selector = term_only;
		tally = 0;
		termoffset = 0;
		fileoffset = 0;
		std::cout << banner << std::endl;
		if (formatident == "")
			std::cout << " (no format preloaded)'" << std::endl;
		else
		{
			slowprint(formatident);
			println();
		}
		std::cout << std::flush;
		jobname = "";
		nameinprogress = false;
		logopened = false;
		outputfilename = "";
		inputptr = 0;
		maxinstack = 0;
		inopen = 0;
		openparens = 0;
		maxbufstack = 0;
		paramptr = 0;
		maxparamstack = 0;
		First = bufsize;
		do
		{
			buffer[First] = 0;
			First--;
		}
		while (First);
		scannerstatus = 0;
		warningindex = 0;
		First = 1;
		state = new_line;
		start = 1;
		index = 0;
		line = 0;
		name = "";
		forceeof = false;
		alignstate = 1000000;
		if (!initterminal())
			throw std::string();
		limit = last;
		First = last+1;
		if (formatident == "" || buffer[loc] == '&')
		{
			if (formatident != "")
				Initialize();
			if (!openfmtfile())
				throw std::string();
			if (!loadfmtfile())
			{
				wclose(fmtfile);
				throw std::string();
			}
			wclose(fmtfile);
			while (loc < limit && buffer[loc] == ' ')
				loc++;
		}
		if (end_line_char_inactive())
			limit--;
		else
			buffer[limit] = end_line_char();
		fixdateandtime();
		if (interaction == batch_mode)
			selector = no_print;
		else
			selector = term_only;
		if (loc < limit && cat_code(buffer[loc]))
			startinput();
		history = spotless;
		auto t = maincontrol();
		finalcleanup(t);
	}
	catch(const std::string &msg)
	{
		if (msg == "jumpout")
			closefilesandterminate();
		readyalready = 0;
	}
}
