#include "boxerror.h"
#include "error.h"
#include "impression.h"
#include "flushnodelist.h"

//! At certain times box 255 is supposed to be void (i.e., |null|),
//! or an insertion box is supposed to be ready to accept a vertical list.
//!  If not, an error message is printed, and the following subroutine
//!  flushes the unwanted contents, reporting them to the user.
void boxerror(eightbits n)
{
	error();
	begindiagnostic();
	printnl("The following box has been deleted:");
	showbox(box(n));
	enddiagnostic(true);
	flushnodelist(box(n));
	box(n) = 0;
}
