#ifndef POLICE_H
#define POLICE_H

#include "globals.h"

class Font
{
	public:
		int charbase;
		int widthbase;
		int heightbase;
		int depthbase;
		int italicbase;
		int ligkernbase;
		int kernbase;
		int extenbase;
		int parambase;
		std::string name;
		std::string area;
		fourquarters check;
		scaled size;
		scaled dsize; 
		fontindex params;
		eightbits bc;
		eightbits ec;
		halfword glue;
		bool used;
		int hyphenchar;
		int skewchar;
		fontindex bcharlabel;
		int bchar; // of 0..256
		int falsebchar; // of 0..256
};

inline Font fonts[fontmax+1];
inline memoryword fontinfo[fontmemsize+1];
inline fontindex fmemptr;
inline internalfontnumber fontptr;
inline internalfontnumber curf;


fourquarters char_info(internalfontnumber, smallnumber);
int char_width(internalfontnumber, fourquarters); 
int char_italic(internalfontnumber, fourquarters);
int char_height(internalfontnumber, fourquarters);
int char_depth(internalfontnumber, fourquarters);
int char_tag(fourquarters);
quarterword skip_byte(fourquarters);
quarterword next_char(fourquarters);
quarterword op_byte(fourquarters); 
quarterword rem_byte(fourquarters);
bool char_exists(fourquarters); 
int char_kern(internalfontnumber, fourquarters); 
int lig_kern_start(internalfontnumber, fourquarters); //!< beginning of lig/kern program
int lig_kern_restart(internalfontnumber, fourquarters); 
int& param(smallnumber, internalfontnumber); 
int& space(internalfontnumber); //!< normal space between words
int& space_stretch(internalfontnumber); //!< stretch between words
int& space_shrink(internalfontnumber); //!< shrink between words
int& x_height(internalfontnumber); //!< one ex
int& quad(internalfontnumber); //!< one em
int mathex(smallnumber); 
int mathsy(smallnumber, smallnumber); 
int axis_height(smallnumber); //!< height of fraction lines above the baseline
int math_x_height(smallnumber); //!< height of `x'
int math_quad(smallnumber); //!< 18mu
internalfontnumber readfontinfo(halfword, const std::string &, const std::string &, scaled);
[[nodiscard]] int findfontdimen(bool);

#endif
