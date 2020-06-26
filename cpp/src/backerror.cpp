#include "backerror.h"
#include "backinput.h"
#include "error.h"

//! Back up one token and call \a error.
//!The \a back_error routine is used when we want to replace an offending token
//!just before issuing an error message. This routine, like \a back_input,
//!requires that \a cur_tok has been set. We disable interrupts during the
//!call of \a back_input so that the help message won't be lost.
void backerror(void)
{
	OKtointerrupt = false;
	backinput();
	OKtointerrupt = true;
	error();
}
