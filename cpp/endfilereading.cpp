#include "endfilereading.h"
#include "aclose.h"

void endfilereading(void)
{
	First = curinput.startfield;
	line = linestack[curinput.indexfield];
	if (curinput.namefield > 17)
		aclose(inputfile[curinput.indexfield]);
	inputptr--;
	curinput = inputstack[inputptr];
	inopen--;
}
