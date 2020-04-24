#include "interror.h"
#include "print.h"
#include "printint.h"
#include "printchar.h"
#include "error.h"

void interror(int n)
{
	print(286); // (
	printint(n);
	printchar(')');
	error();
}
