#include "boxerror.h"
#include "error.h"
#include "begindiagnostic.h"
#include "printnl.h"
#include "showbox.h"
#include "enddiagnostic.h"
#include "flushnodelist.h"

void boxerror(eightbits n)
{
	error();
	begindiagnostic();
	printnl(835); //The following box has been deleted:
	showbox(eqtb[3678+n].hh.rh);
	enddiagnostic(true);
	flushnodelist(eqtb[3678+n].hh.rh);
	eqtb[3678+n].hh.rh = 0;
}
