#include "charbox.h"
#include "noeud.h"
#include "police.h"

halfword charbox(const Font &ft, quarterword c)
{
	auto b = newnullbox();
	width(b) = ft.char_width(c)+ft.char_italic(c);
	height(b) = ft.char_height(c);
	depth(b) = ft.char_depth(c);
	auto p = new CharNode;
	p->character = c;
	p->font = f/*t*/;
	list_ptr(b) = p->num;
	return b;
}
