#include "globals.h"
#include "initialize.h"
#include "initprim.h"
#include "getstringsstarted.h"
#include "fixdateandtime.h"
#include "slowprint.h"
#include "println.h"
#include "openfmtfile.h"
#include "initterminal.h"
#include "loadfmtfile.h"
#include "startinput.h"
#include "wclose.h"
#include "maincontrol.h"
#include "finalcleanup.h"
#include "closefilesandterminate.h"
#include <iostream>

int main()
{
	try
	{
		history = 3;
		if (readyalready != 314159)
		{
			bad = 0;
			if (halferrorline < 30 || halferrorline > errorline-15)
				bad = 1;
			if (maxprintline < 60)
				bad = 2;
			if (dvibufsize%8)
				bad = 3;
			if (1100 > 30000)
				bad = 4;
			if (1777 > 2100)
				bad = 5;
			if (maxinopen >= 128)
				bad = 6;
			if (30000 < 267)
				bad = 7;
			if (memmin != 0 || memmax != 30000)
				bad = 10;
			if (memmin > 0 || memmax < 30000)
				bad = 10;
			if (0 > 0 || 255 < 127)
				bad = 11;
			if (0 > 0 || 65535 < 32767)
				bad = 12;
			if (0 < 0 || 255 > 65535)
				bad = 13;
			if (memmin < 0 || memmax >= 65535 || -0-memmin > 65536)
				bad = 14;
			if (0 < 0 || fontmax > 255)
				bad = 15;
			if (fontmax > 256)
				bad = 16;
			if (savesize > 65535 || maxstrings > 65535) 
				bad = 17;
			if (bufsize > 65535)
				bad = 18;
			if (255 < 255)
				bad = 19;
			if (6976 > 65535)
				bad = 21;
			if (20 > filenamesize)
				bad = 31;
			if (2*65535 < 30000-memmin)
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
			initstrptr = strptr;
			initpoolptr = poolptr;
			fixdateandtime();
			readyalready = 314159;
		}
		selector = 17;
		tally = 0;
		termoffset = 0;
		fileoffset = 0;
		std::cout << "This is TeX, Version 3.14159265" << std::endl;
		if (formatident == 0)
			std::cout << " (no format preloaded)'" << std::endl;
		else
		{
			slowprint(formatident);
			println();
		}
		std::cout << std::flush;
		jobname = 0;
		nameinprogress = false;
		logopened = false;
		outputfilename = 0;
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
		curinput.statefield = 33;
		curinput.startfield = 1;
		curinput.indexfield = 0;
		line = 0;
		curinput.namefield = 0;
		forceeof = false;
		alignstate = 1000000;
		if (!initterminal())
			throw std::string();
		curinput.limitfield = last;
		First = last+1;
		if (formatident == 0 || buffer[curinput.locfield] == '&')
		{
			if (formatident)
				Initialize();
			if (!openfmtfile())
				throw std::string();
			if (!loadfmtfile())
			{
				wclose(fmtfile);
				throw std::string();
			}
			wclose(fmtfile);
			while (curinput.locfield < curinput.limitfield && buffer[curinput.locfield] == ' ')
				curinput.locfield++;
		}
		if (int_par(end_line_char_code) < 0 || int_par(end_line_char_code) > 255)
			curinput.limitfield--;
		else
			buffer[curinput.limitfield] = int_par(end_line_char_code);
		fixdateandtime();
		magicoffset = strstart[891]-9*16;
		if (interaction == 0)
			selector = 16;
		else
			selector = 17;
		if (curinput.locfield < curinput.limitfield && cat_code(buffer[curinput.locfield]))
			startinput();
		history = 0;
		maincontrol();
		finalcleanup();
	}
	catch(const std::string &msg)
	{
		if (msg == "jumpout")
			closefilesandterminate();
		readyalready = 0;
	}
}
