#include "scansomethinginternal.h"
#include "scancharnum.h"
#include "printnl.h"
#include "print.h"
#include "backerror.h"
#include "scaneightbitint.h"
#include "backinput.h"
#include "scanfontident.h"
#include "findfontdimen.h"
#include "printcmdchr.h"
#include "printesc.h"
#include "error.h"
#include "muerror.h"
#include "newspec.h"


void scansomethinginternal(smallnumber level, bool negative)
{
	halfword m = curchr;
	switch (curcmd)
	{
		case def_code:
			scancharnum();
			if (m == math_code_base)
			{
				curval = math_code(curval);
				curvallevel = 0;
			}
			else 
				if (m < math_code_base)
				{
					curval = equiv(m+curval);
					curvallevel = 0;
				}
				else
				{
					curval = eqtb[m+curval].int_;
					curvallevel = 0;
				}
			break;
		case toks_register:
		case assign_toks:
		case def_family:
		case set_font:
		case def_font:
			if (level != 5)
			{
				printnl(262); //! 
				print(664); //Missing number, treated as zero
				helpptr = 3;
				helpline[2] = 665; //A number should have been here; I inserted `0'.
				helpline[1] = 666; //(If you can't figure out why I needed to see a number,
				helpline[0] = 667; //look up `weird error' in the index to The TeXbook.)
				backerror();
				curval = 0;
				curvallevel = 1;
			}
			else 
				if (curcmd <= assign_toks)
				{
					if (curcmd < assign_toks)
					{
						scaneightbitint;
						m = toks_base+curval;
					}
					curval = equiv(m);
					curvallevel = 5;
				}
				else
				{
					backinput();
					scanfontident();
					curval += frozen_null_font;
					curvallevel = 4;
				}
			break;
		case assign_int:
			curval = eqtb[m].int_;
			curvallevel = 0;
			break;
		case assign_dimen:
			curval = eqtb[m].int_;
			curvallevel = 1;
			break;
		case assign_glue:
			curval = equiv(m);
			curvallevel = 2;
			break;
		case assign_mu_glue:
			curval = equiv(m);
			curvallevel = 3;
			break;
		case set_aux:
			if (abs(mode) != m)
			{
				printnl(262); //! 
				print(680); //Improper 
				printcmdchr(set_aux, m);
				helpptr = 4;
				helpline[3] = 681; // You can refer to \spacefactor only in horizontal mode;
				helpline[2] = 682; //you can refer to \prevdepth only in vertical mode; and
				helpline[1] = 683; //neither of these is meaningful inside \write. So
				helpline[0] = 684; //I'm forgetting what you said and using zero instead.
				error();
				if (level != 5)
				{
					curval = 0;
					curvallevel = 1;
				}
				else
				{
					curval = 0;
					curvallevel = 0;
				}
			}
			else 
				if (m == 1)
				{
					curval = prev_depth;
					curvallevel = 1;
				}
				else
				{
					curval = space_factor;
					curvallevel = 0;
				}
			break;
		case set_prev_graf:
			if (mode == 0)
			{
				curval = 0;
				curvallevel = 0;
			}
			else
			{
				nest[nestptr] = curlist;
				auto p = nestptr;
				while (abs(nest[p].modefield) != vmode)
					p--;
				curval = nest[p].pgfield;
				curvallevel = 0;
			}
			break;
		case set_page_int:
			if (m == 0)
				curval = deadcycles;
			else
				curval = insertpenalties;
			curvallevel = 0;
			break;
		case set_page_dimen:
			if (pagecontents == 0 && !outputactive)
				if (m == 0)
					curval = max_dimen;
				else
					curval = 0;
			else
				curval = pagesofar[m];
			curvallevel = 1;
			break;
		case set_shape:
			if (par_shape_ptr() == 0)
				curval = 0;
			else
				curval = info(par_shape_ptr());
			curvallevel = 0;
			break;
		case set_box_dimen:
			scaneightbitint();
			if (box(curval) == 0)
				curval = 0;
			else
				curval = mem[box(curval)+m].int_;
			curvallevel = 1;
		break;
		case char_given:
		case math_given:
			curval = curchr;
			curvallevel = 0;
			break;
		case assign_font_dimen:
			findfontdimen(false);
			fontinfo[fmemptr].int_ = 0;
			curval = fontinfo[curval].int_;
			curvallevel = 1;
			break;
		case assign_font_int:
			scanfontident();
			if (m == 0)
			{
				curval = hyphenchar[curval];
				curvallevel = 0;
			}
			else
			{
				curval = skewchar[curval];
				curvallevel = 0;
			};
			break;
		case register_:
			scaneightbitint();
			switch (m)
			{
				case 0: 
					curval = count(curval);
					break;
				case 1: 
					curval = dimen(curval);
					break;
				case 2: 
					curval = skip(2900);
					break;
				case 3: 
					curval = mu_skip(3156);
			};
			curvallevel = m;
			break;
		case last_item:
			if (curchr > 2)
			{
				if (curchr == 3)
					curval = line;
				else
					curval = lastbadness;
				curvallevel = 0;
			}
			else
			{
				if (curchr == 2)
					curval = 0;
				else
					curval = 0;
				curvallevel = curchr;
				if (tail < himemmin && mode)
					switch (curchr)
					{
						case 0: 
							if (type(tail) == 12)
								curval = mem[tail+1].int_;
							break;
						case 1: 
							if (type(tail) == 11)
								curval = mem[tail+1].int_;
							break;
						case 2: 
							if (type(tail) == 10)
							{
								curval = info(tail+1);
								if (subtype(tail) == 99)
									curvallevel = 3;
							}
					}
				else 
					if (mode == vmode && tail == head)
						switch (curchr)
						{
							case 0: 
								curval = lastpenalty;
								break;
							case 1: 
								curval = lastkern;
								break;
							case 2: 
								if (lastglue != 0xFF'FF)
									curval = lastglue;
						}
			}
			break;
		default:
			printnl(262); //! 
			print(685); //You can't use `
			printcmdchr(curcmd, curchr);
			print(686); //' after 
			printesc(537); //the
			helpptr = 1;
			helpline[0] = 684; //I'm forgetting what you said and using zero instead.
			error();
			if (level != 5)
			{
				curval = 0;
				curvallevel = 1;
			}
			else
			{
				curval = 0;
				curvallevel = 0;
			}
	};
	while (curvallevel > level)
	{
		if (curvallevel == 2)
			curval = mem[curval+1].int_;
		else 
			if (curvallevel == 3)
			muerror();
		curvallevel--;
	}
	if (negative)
		if (curvallevel >= 2)
		{
			curval = newspec(curval);
			mem[curval+1].int_ = -mem[curval+1].int_;
			mem[curval+2].int_ = -mem[curval+2].int_;
			mem[curval+3].int_ = -mem[curval+3].int_;
		}
		else
			curval = -curval;
	else 
		if (curvallevel >= 2 && curvallevel <= 3)
			link(curval)++;
}
