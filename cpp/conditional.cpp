#include "conditional.h"
#include "getnode.h"
#include "getxtoken.h"
#include "scanint.h"
#include "scandimen.h"
#include "printnl.h"
#include "print.h"
#include "printcmdchr.h"
#include "backerror.h"
#include "scaneightbitint.h"
#include "getnext.h"
#include "scanfourbitint.h"
#include "begindiagnostic.h"
#include "printint.h"
#include "printchar.h"
#include "enddiagnostic.h"
#include "freenode.h"
#include "passtext.h"
#include "changeiflimit.h"
#include "printesc.h"
#include "error.h"
#include "texte.h"

void conditional(void)
{

	auto p = getnode(2);
	link(p) = condptr;
	type(p) = iflimit;
	subtype(p) = curif;
	if_line_field(p) = ifline;
	condptr = p;
	curif = curchr;
	iflimit = 1;
	ifline = line;
	auto savecondptr = condptr;
	smallnumber thisif = curchr;
	halfword q;
	int r;
	bool b;
	int m, n;
	smallnumber savescannerstatus;
	switch (thisif)
	{
		case if_char_code:
		case if_cat_code:
			getxtoken();
			if (curcmd == escape && curchr == 257)
			{
				curcmd = active_char;
				curchr = curtok-0x10'00; //cmd=char_num?
			}
			if (curcmd > 13 || curchr > 255)
			{
				m = 0;
				n = 256;
			}
			else
			{
				m = curcmd;
				n = curchr;
			}
			getxtoken;
			if (curcmd == escape && curchr == 257)
			{
				curcmd = active_char;
				curchr = curtok-0x10'00; //cmd=char_num?
			}
			if (curcmd > 13 || curchr > 255)
			{
				curcmd = 0;
				curchr = 256;
			}
			if (thisif == if_char_code)
				b = n == curchr;
			else
				b = m == curcmd;
			break;
		case if_int_code:
		case if_dim_code:
			if (thisif == if_int_code)
				scanint();
			else
				scandimen(false, false,	false);
			n = curval;
			do
				getxtoken();
			while (curcmd == spacer);
			if (curtok >= 0x0C'00+'<' && curtok <= 0x0C'00+'>')
				r = curtok-0x0C'00;
			else
			{
				printnl("! ");
				print("Missing = inserted for ");
				printcmdchr(if_test, thisif);
				helpptr = 1;
				helpline[0] = "I was expecting to see `<', `=', or `>'. Didn't.";
				backerror();
				r = '=';
			}
			if (thisif == if_int_code)
				scanint();
			else
				scandimen(false, false, false);
			switch (r)
			{
				case '<': 
					b = n < curval;
					break;
				case '=': 
					b = n == curval;
					break;
				case '>': 
					b = n > curval;
			}
			break;
		case if_odd_code:
			scanint();
			b = curval%2;
			break;
		case if_vmode_code: 
			b = abs(mode) == vmode;
			break;
		case if_hmode_code: 
			b = abs(mode) == hmode;
			break;
		case if_mmode_code: 
			b = abs(mode) == mmode;
			break;
		case if_inner_code: 
			b = mode < 0;
			break;
		case if_void_code:
		case if_hbox_code:
		case if_vbox_code:
			scaneightbitint();
			p = box(curval);
			if (thisif == if_void_code)
				b = p == 0;
			else 
				if (p == 0)
					b = false;
				else 
					if (thisif == if_hbox_code)
						b = type(p) == 0;
					else
						b = type(p) == 1;
			break;
		case ifx_code:
			savescannerstatus = scannerstatus;
			scannerstatus = 0;
			getnext();
			n = curcs;
			p = curcmd;
			q = curchr;
			getnext();
			if (curcmd != p)
				b = false;
			else 
				if (curcmd < call)
					b = curchr == q;
				else
				{
					p = link(curchr);
					q = link(equiv(n));
					if (p == q)
						b = true;
					else
					{
						while (p && q)
							if (info(p) != info(q))
								p = 0;
							else
							{
								p = link(p);
								q = link(q);
							}
						b = p == 0 && q == 0;
					}
				}
			scannerstatus = savescannerstatus;
			break;
		case if_eof_code:
			scanfourbitint();
			b = readopen[curval] == 2;
			break;
		case if_true_code: 
			b = true;
			break;
		case if_false_code: 
			b = false;
			break;
		case if_case_code:
			scanint();
			n = curval;
			if (int_par(tracing_commands_code) > 1)
			{
				begindiagnostic();
				print("{case ");
				printint(n);
				printchar('}');
				enddiagnostic(false);
			}
			while (n)
			{
				passtext();
				if (condptr == savecondptr)
					if (curchr == 4)
						n--;
					else
					{
						if (curchr == 2)
						{
							p = condptr;
							ifline = if_line_field(p);
							curif = subtype(p);
							iflimit = type(p);
							condptr = link(p);
							freenode(p, 2);
						}
						else
							iflimit = 2;
						return;
					}
				else 
					if (curchr == 2)
					{
						p = condptr;
						ifline = if_line_field(p);
						curif = subtype(p);
						iflimit = type(p);
						condptr = link(p);
						freenode(p, 2);
					}
			}
			changeiflimit(4, savecondptr);
			return;
	}
	if (int_par(tracing_commands_code) > 1)
	{
		begindiagnostic();
		if (b)
			print("{true}");
		else
			print("{false}");
		enddiagnostic(false);
	}
	if (b)
	{
		changeiflimit(3, savecondptr);
		return;
	}
	while (true)
	{
		passtext();
		if (condptr == savecondptr)
		{
			if (curchr != 4)
			{
				if (curchr == 2)
				{
					p = condptr;
					ifline = if_line_field(p);
					curif = subtype(p);
					iflimit = type(p);
					condptr = link(p);
					freenode(p, 2);
				}
				else
					iflimit = 2;
				return;
			}
			printnl("! "); 
			print("Extra ");
			printesc("or");
			helpptr = 1;
			helpline[0] = "I'm ignoring this; it doesn't match any \\if.";
			error();
		}
		else 
			if (curchr == 2)
			{
				p = condptr;
				ifline = if_line_field(p);
				curif = subtype(p);
				iflimit = type(p);
				condptr = link(p);
				freenode(p, 2);
			}
	}
}
