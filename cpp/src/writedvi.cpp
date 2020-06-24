#include "writedvi.h"

void writedvi(dviindex a, dviindex  b)
{
	for (auto k = a; k <= b; k++)
		dvifile << dvibuf[k];
}
