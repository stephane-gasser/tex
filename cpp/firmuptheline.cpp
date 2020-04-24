#include "firmuptheline.h"
#include "println.h"
#include "print.h"
#include "terminput.h"
#include "constantes.h"

void firmuptheline(void)
{
	curinput.limitfield = last;
	if (int_par(pausing_code) > 0 && interaction > 1)
		{
			println();
			if (curinput.startfield < curinput.limitfield)
				for (int k = curinput.startfield; k < curinput.limitfield; k++)
					print(buffer[k]);
			First = curinput.limitfield;
			print(618); //=>
			terminput();
			if (last > First)
			{
				for (int k = First; k < last; k++)
					buffer[k+curinput.startfield-First] = buffer[k];
				curinput.limitfield = curinput.startfield+last-First;
			}
		}
}
