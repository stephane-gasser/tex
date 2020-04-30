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
	showbox(box(n));
	enddiagnostic(true);
	flushnodelist(box(n));
	box(n) = 0;
}
