#include "printparam.h"
#include "printesc.h"
#include "print.h"

void printparam(int n)
{
	switch (n)
	{
		case 0:
			printesc(420); //pretolerance
			break;
		case 1:
			printesc(421); //tolerance
			break;
		case 2:
			printesc(422); //linepenalty
			break;
		case 3:
			printesc(423); //hyphenpenalty
			break;
		case 4:
			printesc(424); //exhyphenpenalty
			break;
		case 5:
			printesc(425); //clubpenalty
			break;
		case 6:
			printesc(426); //widowpenalty
			break;
		case 7:
			printesc(427); //displaywidowpenalty
			break;
		case 8:
			printesc(428); //brokenpenalty
			break;
		case 9:
			printesc(429); //binoppenalty
			break;
		case 10:
			printesc(430); //relpenalty
			break;
		case 11:
			printesc(431); //predisplaypenalty
			break;
		case 12:
			printesc(432); //postdisplaypenalty
			break;
		case 13:
			printesc(433); //interlinepenalty
			break;
		case 14:
			printesc(434); //doublehyphendemerits
			break;
		case 15:
			printesc(435); //finalhyphendemerits
			break;
		case 16:
			printesc(436); //adjdemerits
			break;
		case 17:
			printesc(437); //mag
			break;
		case 18:
			printesc(438); //delimiterfactor
			break;
		case 19:
			printesc(439); //looseness
			break;
		case 20:
			printesc(440); //time
			break;
		case 21:
			printesc(441); //day
			break;
		case 22:
			printesc(442); //month
			break;
		case 23:
			printesc(443); //year
			break;
		case 24:
			printesc(444); //showboxbreadth
			break;
		case 25:
			printesc(445); //showboxdepth
			break;
		case 26:
			printesc(446); //hbadness
			break;
		case 27:
			printesc(447); //vbadness
			break;
		case 28:
			printesc(448); //pausing
			break;
		case 29:
			printesc(449); //tracingonline
			break;
		case 30:
			printesc(450); //tracingmacros
			break;
		case 31:
			printesc(451); //tracingstats
			break;
		case 32:
			printesc(452); //tracingparagraphs
			break;
		case 33:
			printesc(453); //tracingpages
			break;
		case 34:
			printesc(454); //tracingoutput
			break;
		case 35:
			printesc(455); //tracinglostchars
			break;
		case 36:
			printesc(456); //tracingcommands
			break;
		case 37:
			printesc(457); //tracingrestores
			break;
		case 38:
			printesc(458); //uchyph
			break;
		case 39:
			printesc(459); //outputpenalty
			break;
		case 40:
			printesc(460); //maxdeadcycles
			break;
		case 41:
			printesc(461); //hangafter
			break;
		case 42:
			printesc(462); //floatingpenalty
			break;
		case 43:
			printesc(463); //globaldefs
			break;
		case 44:
			printesc(464); //fam
			break;
		case 45:
			printesc(465); //escapechar
			break;
		case 46:
			printesc(466); //defaulthyphenchar
			break;
		case 47:
			printesc(467); //defaultskewchar
			break;
		case 48:
			printesc(468); //endlinechar
			break;
		case 49:
			printesc(469); //newlinechar
			break;
		case 50:
			printesc(470); //language
			break;
		case 51:
			printesc(471); //lefthyphenmin
			break;
		case 52:
			printesc(472); //righthyphenmin
			break;
		case 53:
			printesc(473); //holdinginserts
			break;
		case 54:
			printesc(474); //errorcontextlines
			break;
		default:
			print(475); //[unknown integer parameter!]
	}
}
