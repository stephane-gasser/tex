#include "newhyphexceptions.h"
#include "scanleftbrace.h"
#include "getxtoken.h"
#include "getavail.h"
#include "impression.h"
#include "error.h"
#include "scancharnum.h"
#include "overflow.h"
#include "makestring.h"
#include "error.h"
#include "texte.h"

void newhyphexceptions(void)
{
	char n, j;
	hyphpointer h;
	halfword p;
	poolpointer u, v;
	scanleftbrace();
	curlang = cur_fam();
	if (curlang < 0 || curlang > 255)
		curlang = 0;
	n = 0;
	p = 0;
	getxtoken();
	while (true)
	{
		switch (curcmd)
		{
			case letter:
			case other_char:
			case char_given:
				if (curchr == '-')
				{
					if (n < 63)
					{
						auto q = getavail();
						link(q) = p;
						info(q) = n;
						p = q;
					}
				}
				else 
					if (lc_code(curchr) == 0)
					{
						print_err("Not a letter");
						helpptr = 2;
						helpline[1] = "Letters in \\hyphenation words must have \\lccode>0.";
						helpline[0] = "Proceed; I'll ignore the character I just read.";
						error();
					}
					else 
						if (n < 63)
						{
							n++;
							hc[n] = lc_code(curchr);
						}
				break;
			case char_num:
				scancharnum();
				curchr = curval;
				curcmd = char_given;
				continue;
			case spacer:
			case right_brace:
				if (n > 1)
				{
					n++;
					hc[n] = curlang;
					str_room(n);
					h = 0;
					for (j = 1; j <= n; j++)
					{
						h = (2*h+hc[j])%hyph_size;
						append_char(hc[j]);
					}
					auto s = makestring();
					if (hyphcount == hyph_size)
						overflow("exception dictionary", hyph_size);
					hyphcount++;
					while (hyphword[h] != "")
					{
						if (hyphword[h].size() < s.size())
						{
							std::swap(hyphlist[h], p);
							std::swap(hyphword[h], s);
						}
						else 
							if (hyphword[h].size() == s.size())
							{
								u = 0;
								v = 0;
								bool label45 = false;
								do
								{
									if (hyphword[h][u] < s[v])
									{
										std::swap(hyphlist[h], p);
										std::swap(hyphword[h], s);
										label45 = true;
									}
									if (hyphword[h][u] > s[v])
										label45 = true;
									if (label45)
										break;
									u++;
									v++;
								} while (u < hyphword[h].size());
								if (!label45)
								{
									std::swap(hyphlist[h], p);
									std::swap(hyphword[h], s);
								}
							}
						if (h > 0)
							h--;
						else
							h = hyph_size;
					}
					hyphword[h] = s;
					hyphlist[h] = p;
				}
				if (curcmd == right_brace)
					return;
				n = 0;
				p = 0;
				break;
			default:
				print_err("Improper "+esc("hyphenation")+" will be flushed");
				helpptr = 2;
				helpline[1] = "Hyphenation exceptions must contain only letters";
				helpline[0] = "and hyphens. But continue; I'll forgive and forget.";
				error();
		}
		getxtoken();
	}
}
