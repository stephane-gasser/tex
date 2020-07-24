#ifndef POLICE_H
#define POLICE_H

#include "globals.h"

class Font
{
	public:
		int charbase; //!< base addresses for |char_info|
		int widthbase; //!< base addresses for widths
		int heightbase; //!< base addresses for heights
		int depthbase; //!< base addresses for depths
		int italicbase; //!< base addresses for italic corrections
		int ligkernbase; //!< base addresses for ligature/kerning programs
		int kernbase; //!< base addresses for kerns
		int extenbase; //!< base addresses for extensible recipes
		int parambase; //!< base addresses for font parameters
		std::string name; //!< name of the font
		std::string area; //!< area of the font
		fourquarters check; //!< check sum
		scaled size; //!< ``at'' size
		scaled dsize; //!< ``design'' size
		fontindex params; //!< how many font parameters are present
		eightbits bc; //!< beginning (smallest) character code
		eightbits ec; //!< ending (largest) character code
		halfword glue; //!< glue specification for interword space, |null| if not allocated
		bool used; //!< has a character from this font actually appeared in the output?
		int hyphenchar;//!< current \.{\\hyphenchar} values
		int skewchar; //!< current \.{\\skewchar} values
		fontindex bcharlabel; //!< start of |lig_kern| program for left boundary character, |non_address| if there is none
		int bchar; //!< right boundary character, |non_char| if there is none
		int falsebchar; //!< |font_bchar| if it doesn't exist in the font, otherwise |non_char|
		fourquarters char_info(smallnumber) const;
		int char_width(smallnumber) const;
		int char_height(smallnumber) const;
		int char_depth(smallnumber) const;
		int char_italic(smallnumber) const;
		int lig_kern_start(fourquarters) const; //!< beginning of lig/kern program
		int lig_kern_restart(fourquarters) const;
		int char_kern(fourquarters) const;
		int& param(smallnumber) const;
		scaled heightplusdepth(quarterword) const;
		int& slant(void) const; //!< slant to the right, per unit distance upward
		int& extra_space(void) const; //!< additional space at end of sentence
		int& space(void) const; //!< normal space between words
		int& space_stretch(void) const; //!< stretch between words
		int& space_shrink(void) const; //!< shrink between words
		int& x_height(void) const; //!< one ex
		int& quad(void) const; //!< one em
		int char_tag(smallnumber);
		bool char_exists(smallnumber);
};

inline std::vector<Font> fonts(1);
inline std::vector<memoryword> fontinfo(7);
inline internalfontnumber curf;

Font& cur_font(void);
int curFontNum(void);
int char_tag(fourquarters);
quarterword skip_byte(fourquarters);
quarterword next_char(fourquarters);
quarterword op_byte(fourquarters); 
quarterword rem_byte(fourquarters);
bool char_exists(fourquarters); 
int& param(smallnumber, internalfontnumber); 
int mathex(smallnumber); 
int mathsy(smallnumber, smallnumber); 
int axis_height(smallnumber); //!< height of fraction lines above the baseline
int math_x_height(smallnumber); //!< height of `x'
int math_quad(smallnumber); //!< 18mu
internalfontnumber readfontinfo(halfword, const std::string &, const std::string &, scaled);
[[nodiscard]] int findfontdimen(bool);
halfword& fam_fnt(halfword);

#endif
