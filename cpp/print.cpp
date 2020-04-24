#include "print.h"
#include "printchar.h"
#include "println.h"
#include "constantes.h"

void print(int s)
{
	if (s >= strptr)
		s = 259; //???
	else 
		if (s < 256)
			if (s < 0)
				s = 259; //???
			else
			{
				if (selector > 20)
				{
					printchar(s);
					return;
				}
				if (s == eqtb[int_base+new_line_char_code].int_)
					if (selector < 20)
					{
						println();
						return;
					}
				int nl = int_par(new_line_char_code);
				int_par(new_line_char_code) = -1;
				for (int j = strstart[s]; j < strstart[s + 1]; j++)
					printchar(strpool[j]);
				int_par(new_line_char_code) = nl;
				return;
			}
	for (int j = strstart[s]; j < strstart[s + 1]; j++)
		printchar(strpool[j]);
}
