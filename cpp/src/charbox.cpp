#include "charbox.h"
#include "newnullbox.h"
#include "getavail.h"

halfword charbox(internalfontnumber f, quarterword c)
{
	auto q = char_info(f, c);
	auto b = newnullbox();
	width(b) = char_width(f, q)+char_italic(f, q);
	height(b) = char_height(f, q);
	depth(b) = char_depth(f, q);
	auto p = getavail();
	subtype(p) = c;
	type(p) = f;
	list_ptr(b) = p;
	return b;
}