#include "print.h"
#include "printchar.h"
#include "println.h"
#include "texte.h"

void print(const std::string &t)
{
	std::string s = t;
	if (txt(s) == 0)
		s = "???";
	else
		if (s.size() == 1)
		{
			if (selector > pseudo)
			{
				printchar(s[0]);
				return;
			}
			unsigned char S = s[0];
			if (S == int_par(new_line_char_code) && selector < pseudo)
			{
				println();
				return;
			}
			int nl = int_par(new_line_char_code);
			int_par(new_line_char_code) = -1;
			for (int j = strstart[S]; j < strstart[S+1]; j++)
				printchar(strpool[j]);
			int_par(new_line_char_code) = nl;
			return;
		}
	for (char c: s)
		printchar(c);
}
