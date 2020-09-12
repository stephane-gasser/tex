#include "globals.h"
#include "initialize.h"
#include "initprim.h"
#include "chaine.h"
#include "fixdateandtime.h"
#include "impression.h"
#include "fichier.h"
#include "fmtfile.h"
#include "startinput.h"
#include "fichier.h"
#include "maincontrol.h"
#include "finalcleanup.h"
#include "dvi.h"
#include "equivalent.h"
#include "erreur.h"
#include <iostream>

static int readyalready;

int main()
{
	try
	{
		history = fatal_error_stop;
		if (readyalready != 314159)
		{
			int bad = 0;
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
			fixdateandtime();
			readyalready = 314159;
		}
		selector = term_only;
		print(banner);
		print("\n"+(formatident == "" ? " (no format preloaded)'" : formatident)+"\n");
		std::cout << std::flush;
		nameinprogress = false;
		std::fill_n(buffer, bufsize+1, '\0');
		state = new_line;
		start = 1;
		index = 0;
		name = "";
		initterminal();
		limit = last;
		First = last+1;
		if (formatident == "" || buffer[loc] == '&')
		{
			if (formatident != "")
				Initialize();
			loadfmtfile();
			for (; loc < limit && buffer[loc] == ' '; loc++); // trim à droite
		}
		if (end_line_char_inactive())
			limit--;
		else
			buffer[limit] = end_line_char();
		fixdateandtime();
		selector = interaction == batch_mode ? no_print : term_only;
		if (loc < limit && cat_code(buffer[loc]))
			startinput();
		history = spotless;
		auto t = maincontrol();
		finalcleanup(t);
	}
	catch (const std::string &msg)
	{
		if (msg == "jumpout")
			closefilesandterminate();
		readyalready = 0;
	}
}
