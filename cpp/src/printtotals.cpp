#include "printtotals.h"
#include "printscaled.h"
#include "print.h"

static void print_plus(int i, const std::string &s)
{
	if (pagesofar[i])
	{
		print(" plus ");
		printscaled(pagesofar[i]);
		print(s);
	}
}

void printtotals(void)
{
	printscaled(page_total);
	print_plus(2, "");
	print_plus(3, "fil");
	print_plus(4, "fill");
	print_plus(5, "filll");
	if (page_shrink)
	{
		print(" minus ");
		printscaled(page_shrink);
	}
}
