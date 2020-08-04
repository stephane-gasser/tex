#include "charbox.h"
#include "noeud.h"
#include "police.h"

BoxNode* charbox(const Font &ft, quarterword c)
{
	auto b = new BoxNode;
	b->width = ft.char_width(c)+ft.char_italic(c);
	b->height = ft.char_height(c);
	b->depth = ft.char_depth(c);
	b->list_ptr = new CharNode(ft, c);
	return b;
}
