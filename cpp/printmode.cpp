#include "printmode.h"
#include "print.h"

void printmode(int m)
{
	if (m > 0)
	switch (m/101)
	{
		case 0: 
			print(355); //vertical
			break;
		case 1: 
			print(356); //horizontal
			break;
		case 2: 
			print(357); //display math
	}
	else 
		if (m == 0)
			print(358); //no
		else
			switch ((-m)/101)
			{
				case 0: 
					print(359); //internal vertical
					break;
				case 1: 
					print(360); //restricted horizontal
					break;
				case 2: 
				print(343); //math
			}
	print(361); // mode
}
