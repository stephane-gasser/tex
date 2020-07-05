#include "beginfilereading.h"
#include "erreur.h"
#include "pushinput.h"

//! The \a begin_file_reading procedure starts a new level of input for lines
//! of characters to be read from a file, or as an insertion from the
//! terminal. It does not take care of opening the file, nor does it set \a loc
//! or \a limit or \a line.
void beginfilereading(void)
{
	if (inopen == maxinopen)
		overflow("text input levels", maxinopen); 
	if (First == bufsize)
		overflow("buffer size", bufsize);
	inopen++;
	push_input();
	index = inopen;
	linestack[index] = line;
	start = First;
	state = mid_line;
	name = "";
	// \a terminal_input is now \a true
}
