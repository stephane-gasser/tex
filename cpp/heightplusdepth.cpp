#include "heightplusdepth.h"

scaled heightplusdepth(internalfontnumber f, quarterword c)
{
	auto q = char_info(f, c);
	return char_height(f, q)+char_depth(f, q);
}
