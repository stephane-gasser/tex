#include "eqdestroy.h"
#include "lecture.h"
#include "deleteglueref.h"
#include "freenode.h"
#include "flushnodelist.h"

void eqdestroy(memoryword w)
{
	halfword q;
	switch (w.hh.b0)
	{
		case 111:
		case 112:
		case 113:
		case 114: 
			deletetokenref(w.hh.rh);
			break;
		case 117: 
			deleteglueref(w.hh.rh);
			break;
		case 118:
			q = w.hh.rh;
			if (q)
				freenode(q, 2*info(q)+1);
			break;
		case 119: 
			flushnodelist(w.hh.rh);
	}
}
