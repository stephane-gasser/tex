#include "printcmdchr.h"
#include "printesc.h"
#include "print.h"
#include "printchar.h"
#include "printscaled.h"
#include "slowprint.h"
#include "printhex.h"
#include "printsize.h"
#include "printint.h"
#include "printparam.h"
#include "printlengthparam.h"
#include "printstyle.h"
#include "printskipparam.h"

void printcmdchr(quarterword cmd, halfword chrcode)
{
	switch (cmd)
	{
		case 1:
			print("begin-group character ");
			printchar(chrcode);
			break;
		case 2:
			print("end-group character ");
			printchar(chrcode);
			break;
		case 3:
			print("math shift character ");
			printchar(chrcode);
			break;
		case 6:
			print("macro parameter character ");
			printchar(chrcode);
			break;
		case 7:
			print("superscript character ");
			printchar(chrcode);
			break;
		case 8:
			print("subscript character ");
			printchar(chrcode);
			break;
		case 9: 
			print("end of alignment template");
			break;
		case 10:
			print("blank space ");
			printchar(chrcode);
			break;
		case 11:
			print("the letter ");
			printchar(chrcode);
			break;
		case 12:
			print("the character ");
			printchar(chrcode);
			break;
		case 75:
		case 76: 
			if (chrcode < 2900)
				printskipparam(chrcode-2882);
			else 
				if (chrcode < 3156)
				{
					printesc("skip");
					printint(chrcode-2900);
				}
				else
				{
					printesc("muskip");
					printint(chrcode-3156);
				}
			break;
		case 72: 
			if (chrcode >= 3422)
			{
				printesc("toks");
				printint(chrcode-3422);
			}
			else
				switch (chrcode)
				{
					case 3413: 
						printesc("output");
						break;
					case 3414: 
						printesc("everypar");
						break;
					case 3415: 
						printesc("everymath");
						break;
					case 3416: 
						printesc("everydisplay");
						break;
					case 3417: 
						printesc("everyhbox");
						break;
					case 3418: 
						printesc("everyvbox");
						break;
					case 3419: 
						printesc("everyjob");
						break;
					case 3420: 
						printesc("everycr");
						break;
					default: 
						printesc("errhelp");
				}
			break;
		case 73: 
			if (chrcode < 5318)
				printparam(chrcode-5263);
			else
			{
				printesc("count");
				printint(chrcode-5318);
			}
			break;
		case 74: 
			if (chrcode < 5851)
				printlengthparam(chrcode-5830);
			else
			{
				printesc("dimen");
				printint(chrcode-5851);
			}
			break;
		case 45: 
			printesc("accent");
			break;
		case 90: 
			printesc("advance");
			break;
		case 40: 
			printesc("afterassignment");
			break;
		case 41: 
			printesc("aftergroup");
			break;
		case 77: 
			printesc("fontdimen");
			break;
		case 61: 
			printesc("begingroup");
			break;
		case 42: 
			printesc("penalty");
			break;
		case 16: 
			printesc("char");
			break;
		case 107: 
			printesc("csname");
			break;
		case 88: 
			printesc("font");
			break;
		case 15: 
			printesc("delimiter");
			break;
		case 92: 
			printesc("divide");
			break;
		case 67: 
			printesc("endcsname");
			break;
		case 62: 
			printesc("endgroup");
			break;
		case 64: 
			printesc(" ");
			break;
		case 102: 
			printesc("expandafter");
			break;
		case 32: 
			printesc("halign");
			break;
		case 36: 
			printesc("hrule");
			break;
		case 39: 
			printesc("ignorespaces");
			break;
		case 37: 
			printesc("insert");
			break;
		case 44: 
			printesc("/");
			break;
		case 18: 
			printesc("mark");
			break;
		case 46: 
			printesc("mathaccent");
			break;
		case 17: 
			printesc("mathchar");
			break;
		case 54: 
			printesc("mathchoice");
			break;
		case 91: 
			printesc("multiply");
			break;
		case 34: 
			printesc("noalign");
			break;
		case 65: 
			printesc("noboundary");
			break;
		case 103: 
			printesc("noexpand");
			break;
		case 55: 
			printesc("nonscript");
			break;
		case 63: 
			printesc("omit");
			break;
		case 66: 
			printesc("radical");
			break;
		case 96: 
			printesc("read");
			break;
		case 0: 
			printesc("relax");
			break;
		case 98: 
			printesc("setbox");
			break;
		case 80: 
			printesc("prevgraf");
			break;
		case 84: 
			printesc("parshape");
			break;
		case 109: 
			printesc("the");
			break;
		case 71: 
			printesc("toks");
			break;
		case 38: 
			printesc("vadjust");
			break;
		case 33: 
			printesc("valign");
			break;
		case 56: 
			printesc("vcenter");
			break;
		case 35: 
			printesc("vrule");
			break;
		case 13: 
			printesc("par");
			break;
		case 104: 
			if (chrcode == 0)
				printesc("input");
			else
				printesc("endinput");
			break;
		case 110: 
			switch (chrcode)
			{
				case 1: 
					printesc("firstmark");
					break;
				case 2: 
					printesc("botmark");
					break;
				case 3: 
					printesc("splitfirstmark");
					break;
				case 4: 
					printesc("splitbotmark");
					break;
				default: 
					printesc("topmark");
			}
			break;
		case 89: 
			if (chrcode == 0)
				printesc("count");
			else 
				if (chrcode == 1)
					printesc("dimen");
				else 
					if (chrcode == 2)
						printesc("skip");
					else
						printesc("muskip");
			break;
		case 79: 
			if (chrcode == 1)
				printesc("prevdepth");
			else
				printesc("spacefactor");
			break;
		case 82: 
			if (chrcode == 0)
				printesc("deadcycles");
			else
				printesc("insertpenalties");
			break;
		case 83: 
			if (chrcode == 1)
				printesc("wd");
			else 
				if (chrcode == 3)
					printesc("ht");
				else
					printesc("dp");
			break;
		case 70: 
			switch (chrcode)
			{
				case 0: 
					printesc("lastpenalty");
					break;
				case 1: 
					printesc("lastkern");
					break;
				case 2: 
					printesc("lastskip");
					break;
				case 3: 
					printesc("inputlineno");
					break;
				default: 
					printesc("badness");
			}
			break;
		case 108: 
			switch (chrcode)
			{
				case 0: 
					printesc("number");
					break;
				case 1: 
					printesc("romannumeral");
					break;
				case 2: 
					printesc("string");
					break;
				case 3: 
					printesc("meaning");
					break;
				case 4: 
					printesc("fontname");
					break;
				default: 
					printesc("jobname");
			}
			break;
		case 105: 
			switch (chrcode)
			{
				case 1: 
					printesc("ifcat");
					break;
				case 2: 
					printesc("ifnum");
					break;
				case 3: 
					printesc("ifdim");
					break;
				case 4: 
					printesc("ifodd");
					break;
				case 5: 
					printesc("ifvmode");
					break;
				case 6: 
					printesc("ifhmode");
					break;
				case 7: 
					printesc("ifmmode");
					break;
				case 8: 
					printesc("ifinner");
					break;
				case 9: 
					printesc("ifvoid");
					break;
				case 10: 
					printesc("ifhbox");
					break;
				case 11: 
					printesc("ifvbox");
					break;
				case 12: 
					printesc("ifx");
					break;
				case 13: 
					printesc("ifeof");
					break;
				case 14: 
					printesc("iftrue");
					break;
				case 15: 
					printesc("iffalse");
					break;
				case 16: 
					printesc("ifcase");
					break;
			default: 
				printesc("if");
			}
			break;
		case 106: 
			if (chrcode == 2)
				printesc("fi");
			else 
				if (chrcode == 4)
					printesc("or");
				else
					printesc("else");
			break;
		case 4: 
			if (chrcode == 256)
				printesc("span");
			else
			{
				print("alignment tab character ");
				printchar(chrcode);
			}
			break;
		case 5: 
			if (chrcode == 257)
				printesc("cr");
			else
				printesc("crcr");
			break;
		case 81: 
			switch (chrcode)
			{
				case 0: 
					printesc("pagegoal");
					break;
				case 1: 
					printesc("pagetotal");
					break;
				case 2: 
					printesc("pagestretch");
					break;
				case 3: 
					printesc("pagefilstretch");
					break;
				case 4: 
					printesc("pagefillstretch");
					break;
				case 5: 
					printesc("pagefilllstretch");
					break;
				case 6: 
					printesc("pageshrink");
					break;
				default: 
					printesc("pagedepth");
			}
			break;
		case 14: 
			if (chrcode == 1)
				printesc("dump");
			else
				printesc("end");
			break;
		case 26: 
			switch (chrcode)
			{
				case 4: 
					printesc("hskip");
					break;
				case 0: 
					printesc("hfil");
					break;
				case 1: 
					printesc("hfill");
					break;
				case 2: 
					printesc("hss");
					break;
				default: 
					printesc("hfilneg");
			}
			break;
		case 27: 
			switch (chrcode)
			{
				case 4: 
					printesc("vskip");
					break;
				case 0: 
					printesc("vfil");
					break;
				case 1: 
					printesc("vfill");
					break;
				case 2: 
					printesc("vss");
					break;
				default: 
					printesc("vfilneg");
			}
			break;
		case 28: 
			printesc("mskip");
			break;
		case 29: 
			printesc("kern");
			break;
		case 30: 
			printesc("mkern");
			break;
		case 21: 
			if (chrcode == 1)
				printesc("moveleft");
			else
				printesc("moveright");
			break;
		case 22: 
			if (chrcode == 1)
				printesc("raise");
			else
				printesc("lower");
			break;
		case 20: 
			switch (chrcode)
			{
				case 0: 
					printesc("box");
					break;
				case 1: 
					printesc("copy");
					break;
				case 2: 
					printesc("lastbox");
					break;
				case 3: 
					printesc("vsplit");
					break;
				case 4: 
					printesc("vtop");
					break;
				case 5: 
					printesc("vbox");
					break;
				default: 
					printesc("hbox");
			}
			break;
		case 31: 
			if (chrcode == 100)
				printesc("leaders");
			else 
				if (chrcode == 101)
					printesc("cleaders");
				else 
					if (chrcode == 102)
						printesc("xleaders");
					else
						printesc("shipout");
			break;
		case 43: 
			if (chrcode == 0)
				printesc("noindent");
			else
				printesc("indent");
			break;
		case 25: 
			if (chrcode == 10)
				printesc("unskip");
				else 
					if (chrcode == 11)
						printesc("unkern");
					else
						printesc("unpenalty");
			break;
		case 23: 
			if (chrcode == 1)
				printesc("unhcopy");
			else
				printesc("unhbox");
			break;
		case 24: 
			if (chrcode == 1)
				printesc("unvcopy");
			else
			printesc("unvbox");
			break;
		case 47: 
			if (chrcode == 1)
				printesc("-");
			else
				printesc("discretionary");
			break;
		case 48: 
			if (chrcode == 1)
				printesc("leqno");
			else
				printesc("eqno");
			break;
		case 50: 
			switch (chrcode)
			{
				case 16: 
					printesc("mathord");
					break;
				case 17: 
					printesc("mathop");
					break;
				case 18: 
					printesc("mathbin");
					break;
				case 19: 
					printesc("mathrel");
					break;
				case 20: 
					printesc("mathopen");
					break;
				case 21: 
					printesc("mathclose");
					break;
				case 22: 
					printesc("mathpunct");
					break;
				case 23: 
					printesc("mathinner");
					break;
				case 26: 
					printesc("overline");
					break;
				default: 
					printesc("underline");
			}
			break;
		case 51: 
			if (chrcode == 1)
			printesc("limits");
			else 
				if (chrcode == 2)
					printesc("nolimits");
				else
				printesc("displaylimits");
			break;
		case 53: 
			printstyle(chrcode);
			break;
		case 52: 
			switch (chrcode)
			{
				case 1: 
					printesc("over");
					break;
				case 2: 
					printesc("atop");
					break;
				case 3: 
					printesc("abovewithdelims");
					break;
				case 4: 
					printesc("overwithdelims");
					break;
				case 5: 
					printesc("atopwithdelims");
					break;
				default: 
					printesc("above");
			}
			break;
		case 49: 
			if (chrcode == 30)
				printesc("left");
			else
				printesc("right");
			break;
		case 93: 
			if (chrcode == 1)
				printesc("long");
			else 
				if (chrcode == 2)
					printesc("outer");
				else
					printesc("global");
		case 97: 
			if (chrcode == 0)
				printesc("def");
			else 
				if (chrcode == 1)
					printesc("gdef");
				else 
					if (chrcode == 2)
						printesc("edef");
					else
						printesc("xdef");
			break;
		case 94: 
			if (chrcode)
				printesc("futurelet");
			else
				printesc("let");
			break;
		case 95: 
			switch (chrcode)
			{
				case 0: 
					printesc("chardef");
					break;
				case 1: 
					printesc("mathchardef");
					break;
				case 2: 
					printesc("countdef");
					break;
				case 3: 
					printesc("dimendef");
					break;
				case 4: 
					printesc("skipdef");
					break;
				case 5: 
					printesc("muskipdef");
					break;
				default: printesc("toksdef");
			}
			break;
		case 68:
			printesc("char");
			printhex(chrcode);
			break;
		case 69:
			printesc("delimiter");
			printhex(chrcode);
			break;
		case 85: 
			if (chrcode == 3983)
				printesc("catcode");
			else 
				if (chrcode == 5007)
					printesc("mathcode");
				else 
					if (chrcode == 4239)
						printesc("lccode");
					else 
						if (chrcode == 4495)
							printesc("uccode");
						else 
							if (chrcode == 4751)
								printesc("sfcode");
							else
								printesc("delcode");
			break;
		case 86: 
			printsize(chrcode-3935);
			break;
		case 99: 
			if (chrcode == 1)
				printesc("patterns");
			else
				printesc("hyphenation");
			break;
		case 78: 
			if (chrcode == 0)
				printesc("hyphenchar");
			else
				printesc("skewchar");
			break;
		case 87:
			print("select font ");
			slowprint(fontname[chrcode]);
			if (fontsize[chrcode] != fontdsize[chrcode])
			{
				print(" at ");
				printscaled(fontsize[chrcode]);
				print("pt");
			}
			break;
		case 100: 
			switch (chrcode)
			{
				case 0: 
					printesc("batchmode");
					break;
				case 1: 
					printesc("nonstopmode");
					break;
				case 2: 
					printesc("scrollmode");
					break;
				default: 
					printesc("errorstopmode");
			}
			break;
		case 60: 
			if (chrcode == 0)
				printesc("closein");
			else
				printesc("openin");
			break;
		case 58: 
			if (chrcode == 0)
				printesc("message");
			else
				printesc("errmessage");
			break;
		case 57: 
			if (chrcode == 4239)
				printesc("lowercase");
			else
				printesc("uppercase");
			break;
		case 19: 
			switch (chrcode)
			{
				case 1: 
					printesc("showbox");
					break;
				case 2: 
					printesc("showthe");
					break;
				case 3: 
					printesc("showlists");
					break;
				default: 
					printesc("show");
			}
			break;
		case 101: 
			print("undefined");
			break;
		case 111: 
			print("macro");
			break;
		case 112: 
			printesc("long macro");
			break;
		case 113: 
			printesc("outer macro");
			break;
		case 114:
			printesc("long");
			printesc("outer macro");
			break;
		case 115: 
			printesc("outer endtemplate");
			break;
		case 59: 
			switch (chrcode)
			{
				case 0: 
					printesc("openout");
					break;
				case 1: 
					printesc("write");
					break;
				case 2: 
					printesc("closeout");
					break;
				case 3: 
					printesc("special");
					break;
				case 4: 
					printesc("immediate");
					break;
				case 5: 
					printesc("setlanguage");
					break;
				default: 
					print("[unknown extension!]");
			}
			break;
		default: 
			print("[unknown command code!]");
	}
}
