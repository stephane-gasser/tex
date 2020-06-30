#include "interror.h"
#include "impression.h"
#include "error.h"

void interror(int n)
{
	print(" ("+std::to_string(n)+")");
	error();
}
