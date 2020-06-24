#include "dvifour.h"
#include "dviswap.h"

void dvifour(int x)
{
	if (x >= 0)
		dvi_out(x/0x1'00'00'00);
	else
	{
		x += 0x80'00'00'00;
		dvi_out((x/0x1'00'00'00)+0x80);
	}
	x %= 0x1'00'00'00;
	dvi_out(x/0x1'00'00);
	x %= 0x1'00'00;
	dvi_out(x/0x1'00);
	dvi_out(x%0x1'00);
}
