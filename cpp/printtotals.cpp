#include "printtotals.h"
#include "printscaled.h"
#include "print.h"

void printtotals(void)
{
	printscaled(pagesofar[1]);
	if (pagesofar[2])
	{
		print(" plus ");
		printscaled(pagesofar[2]);
		print("");
	}
	if (pagesofar[3])
	{
		print(" plus ");
		printscaled(pagesofar[3]);
		print("fil");
	}
	if (pagesofar[4])
	{
		print(" plus ");
		printscaled(pagesofar[4]);
		print("fill");
	}
	if (pagesofar[5])
	{
		print(" plus ");
		printscaled(pagesofar[5]);
		print("filll");
	}
	if (pagesofar[6])
	{
		print(" minus ");
		printscaled(pagesofar[6]);
	}
}
