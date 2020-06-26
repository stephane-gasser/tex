#include "interror.h"
#include "impression.h"
#include "error.h"

void interror(int n)
{
	print(" (");
	printint(n);
	printchar(')');
	error();
}
