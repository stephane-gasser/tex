#ifndef LECTURE_H
#define LECTURE_H

#include "globals.h"
#include "token.h"

enum token_type
{
	parameter = 0, //!< \a token_type code for parameter
	u_template = 1, //!< \a token_type code for \f$<u_j>\f$ template
	v_template = 2, //!< \a token_type code for \f$<v_j>\f$ template
	backed_up = 3, //!< \a token_type code for text to be reread
	inserted = 4, //!< \a token_type code for inserted texts
	macro = 5, //!< \a token_type code for defined control sequences
	output_text = 6, //!< \a token_type code for output routines
	every_par_text = 7, //!< \a token_type code for \\everypar
	every_math_text = 8, //!< \a token_type code for \\everymath
	every_display_text = 9, //!< \a token_type code for \\everydisplay
	every_hbox_text = 10, //!< \a token_type code for \\everyhbox
	every_vbox_text = 11, //!< \a token_type code for \\everyvbox
	every_job_text = 12, //!< \a token_type code for \\everyjob
	every_cr_text = 13, //!< \a token_type code for \\everycr
	mark_text = 14, //!< \a token_type code for \\topmark, etc.
	write_text = 15 //!< \a token_type code for \\write
};

inline smallnumber radix = 0;
inline glueord curorder = 0;

void endtokenlist(void);
TokenList thetoks(char);


inline void backList(const TokenList &tl) { tl.beginBelowMacro(backed_up); } //!< backs up a simple token list
inline void insList(const TokenList &tl) { tl.beginBelowMacro(inserted); } //!< inserts a simple token list

#endif
