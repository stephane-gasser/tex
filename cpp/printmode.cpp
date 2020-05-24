#include "printmode.h"
#include "print.h"

void printmode(int m)
{
	if (m > 0)
	switch (m/101)
	{
		case 0: 
			print("vertical");
			break;
		case 1: 
			print("horizontal");
			break;
		case 2: 
			print("display math");
	}
	else 
		if (m == 0)
			print("no");
		else
			switch ((-m)/101)
			{
				case 0: 
					print("internal vertical");
					break;
				case 1: 
					print("restricted horizontal");
					break;
				case 2: 
				print("math");
			}
	print(" mode");
}
