#include "printtotals.h"
#include "printscaled.h"
#include "print.h"

void printtotals(void)
{
	printscaled(pagesofar[1]);
	if (pagesofar[2])
	{
		print(312); // plus 
		printscaled(pagesofar[2]);
		print(338); //
	}
	if (pagesofar[3])
	{
		print(312); // plus 
		printscaled(pagesofar[3]);
		print(311); //fil
	}
	if (pagesofar[4])
	{
		print(312); // plus 
		printscaled(pagesofar[4]);
		print(977); //fill
	}
	if (pagesofar[5])
	{
		print(312); // plus 
		printscaled(pagesofar[5]);
		print(978); //filll
	}
	if (pagesofar[6])
	{
		print(313); // minus 
		printscaled(pagesofar[6]);
	}
}
