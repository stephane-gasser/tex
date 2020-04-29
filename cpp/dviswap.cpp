#include "dviswap.h"
#include "writedvi.h"

void dviswap(void)
{
	if (dvilimit == dvibufsize)
	{
		writedvi(0, halfbuf-1);
		dvilimit = halfbuf;
		dvioffset = dvioffset+dvibufsize;
		dviptr = 0;
	}
	else
	{
		writedvi(halfbuf, dvibufsize-1);
		dvilimit = dvibufsize;
	}
	dvigone = dvigone+halfbuf;
}
