#include "makemark.h"
#include "lecture.h"
#include "noeud.h"

void makemark(Token t)
{
	auto q = scantoks(false, true, t);
	tail_append(new MarkNode);
}
