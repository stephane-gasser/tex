#include "charwarning.h"
#include "impression.h"
#include "police.h"
#include "equivalent.h"

void charwarning(const Font &ft, eightbits c)
{
	if (tracing_lost_chars() > 0)
		diagnostic("\rMissing character: There is no "+std::string(1, c)+" in font "+ft.name+"!");
}
