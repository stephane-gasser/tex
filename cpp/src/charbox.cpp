#include "charbox.h"
#include "noeud.h"
#include "getavail.h"
#include "police.h"

halfword charbox(const Font &ft, quarterword c)
{
	auto b = newnullbox();
	width(b) = ft.char_width(c)+ft.char_italic(c);
	height(b) = ft.char_height(c);
	depth(b) = ft.char_depth(c);
	auto p = getavail();
	subtype(p) = c;
	type(p) = f;
	list_ptr(b) = p;
	return b;
}
