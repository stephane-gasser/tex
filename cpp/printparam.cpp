#include "printparam.h"
#include "printesc.h"
#include "print.h"

void printparam(int n)
{
	switch (n)
	{
		case 0:
			printesc("pretolerance");
			break;
		case 1:
			printesc("tolerance");
			break;
		case 2:
			printesc("linepenalty");
			break;
		case 3:
			printesc("hyphenpenalty");
			break;
		case 4:
			printesc("exhyphenpenalty");
			break;
		case 5:
			printesc("clubpenalty");
			break;
		case 6:
			printesc("widowpenalty");
			break;
		case 7:
			printesc("displaywidowpenalty");
			break;
		case 8:
			printesc("brokenpenalty");
			break;
		case 9:
			printesc("binoppenalty");
			break;
		case 10:
			printesc("relpenalty");
			break;
		case 11:
			printesc("predisplaypenalty");
			break;
		case 12:
			printesc("postdisplaypenalty");
			break;
		case 13:
			printesc("interlinepenalty");
			break;
		case 14:
			printesc("doublehyphendemerits");
			break;
		case 15:
			printesc("finalhyphendemerits");
			break;
		case 16:
			printesc("adjdemerits");
			break;
		case 17:
			printesc("mag");
			break;
		case 18:
			printesc("delimiterfactor");
			break;
		case 19:
			printesc("looseness");
			break;
		case 20:
			printesc("time");
			break;
		case 21:
			printesc("day");
			break;
		case 22:
			printesc("month");
			break;
		case 23:
			printesc("year");
			break;
		case 24:
			printesc("showboxbreadth");
			break;
		case 25:
			printesc("showboxdepth");
			break;
		case 26:
			printesc("hbadness");
			break;
		case 27:
			printesc("vbadness");
			break;
		case 28:
			printesc("pausing");
			break;
		case 29:
			printesc("tracingonline");
			break;
		case 30:
			printesc("tracingmacros");
			break;
		case 31:
			printesc("tracingstats");
			break;
		case 32:
			printesc("tracingparagraphs");
			break;
		case 33:
			printesc("tracingpages");
			break;
		case 34:
			printesc("tracingoutput");
			break;
		case 35:
			printesc("tracinglostchars");
			break;
		case 36:
			printesc("tracingcommands");
			break;
		case 37:
			printesc("tracingrestores");
			break;
		case 38:
			printesc("uchyph");
			break;
		case 39:
			printesc("outputpenalty");
			break;
		case 40:
			printesc("maxdeadcycles");
			break;
		case 41:
			printesc("hangafter");
			break;
		case 42:
			printesc("floatingpenalty");
			break;
		case 43:
			printesc("globaldefs");
			break;
		case 44:
			printesc("fam");
			break;
		case 45:
			printesc("escapechar");
			break;
		case 46:
			printesc("defaulthyphenchar");
			break;
		case 47:
			printesc("defaultskewchar");
			break;
		case 48:
			printesc("endlinechar");
			break;
		case 49:
			printesc("newlinechar");
			break;
		case 50:
			printesc("language");
			break;
		case 51:
			printesc("lefthyphenmin");
			break;
		case 52:
			printesc("righthyphenmin");
			break;
		case 53:
			printesc("holdinginserts");
			break;
		case 54:
			printesc("errorcontextlines");
			break;
		default:
			print("[unknown integer parameter!]");
	}
}
