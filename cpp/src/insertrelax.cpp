#include "insertrelax.h"
#include "noeud.h"
#include "backinput.h"
#include "equivalent.h"

void insertrelax(halfword cs)
{
	backinput(make_tok(cs_token_flag+cs));
	backinput(make_tok(cs_token_flag+frozen_relax));
	token_type = inserted;
}
