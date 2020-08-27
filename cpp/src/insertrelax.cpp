#include "insertrelax.h"
#include "noeud.h"
#include "backinput.h"

static Token makeCS(halfword cs)
{
	Token t;
	t.tok = cs_token_flag+cs;
	return t;
}

void insertrelax(halfword cs)
{
	backinput(makeCS(cs));
	backinput(makeCS(frozen_relax));
	token_type = inserted;
}
