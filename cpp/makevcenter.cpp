#include "makevcenter.h"
#include "confusion.h"	
#include "half.h"	

void makevcenter(halfword q)
{
	halfword v = info(nucleus(q));
	if (type(v) != vlist_node)
		confusion(539); //vcenter
	scaled delta = height(v)+depth(v);
	height(v) = axis_height(cursize)+half(delta);
	depth(v) = delta-height(v);
}

