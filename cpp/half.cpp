#include "half.h"

int half(int x)
{
	if (x%2)
		return (x + 1)/2;
	else
		return x/2;
}
