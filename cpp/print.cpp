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
			if (S == new_line_char() && selector < pseudo)
			{
				println();
				return;
			}
			int nl = new_line_char();
			new_line_char() = -1;
			for (char c: s)
				printchar(c);
			new_line_char() = nl;
			return;
		}
	for (char c: s)
		printchar(c);
}
