#include "endfilereading.h"
#include "fichier.h"
#include "texte.h"
#include "popinput.h"

void endfilereading(void)
{
	First = start;
	line = linestack[index];
	if (txt(name) > 17)
		aclose(cur_file());
	pop_input();
	inopen--;
}
