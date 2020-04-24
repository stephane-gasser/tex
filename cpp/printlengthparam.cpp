#include "printlengthparam.h"
#include "printesc.h"
#include "print.h"

void printlengthparam(int n)
{
	switch (n)
	{
		case 0:
			printesc(478); //parindent
			break;
		case 1:
			printesc(479); //mathsurround
			break;
		case 2:
			printesc(480); //lineskiplimit
			break;
		case 3:
			printesc(481); //hsize
			break;
		case 4:
			printesc(482); //vsize
			break;
		case 5:
			printesc(483); //maxdepth
			break;
		case 6:
			printesc(484); //splitmaxdepth
			break;
		case 7:
			printesc(485); //boxmaxdepth
			break;
		case 8:
			printesc(486); //hfuzz
			break;
		case 9:
			printesc(487); //vfuzz
			break;
		case 10:
			printesc(488); //delimitershortfall
			break;
		case 11:
			printesc(489); //nulldelimiterspace
			break;
		case 12:
			printesc(490); //scriptspace
			break;
		case 13:
			printesc(491); //predisplaysize
			break;
		case 14:
			printesc(492); //displaywidth
			break;
		case 15:
			printesc(493); //displayindent
			break;
		case 16:
			printesc(494); //overfullrule
			break;
		case 17:
			printesc(495); //hangindent
			break;
		case 18:
			printesc(496); //hoffset
			break;
		case 19:
			printesc(497); //voffset
			break;
		case 20:
			printesc(498); //emergencystretch
			break;
		default:
			print(499); //[unknown dimen parameter!]
	}
}
