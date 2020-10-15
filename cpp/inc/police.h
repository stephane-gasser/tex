#ifndef POLICE_H
#define POLICE_H

#include "globals.h"

enum
{
	slant_code = 1,
	space_code = 2,
	space_stretch_code = 3,
	space_shrink_code = 4,
	x_height_code = 5,
	quad_code = 6,
	extra_space_code = 7
};

class GlueSpec;

class Font
{
	public:
		static std::vector<memoryword> info; //!< the big collection of font data
		static fourquarters& infos(int);
		static quarterword skip_byte(int);
		static quarterword next_char(int);
		static quarterword op_byte(int);
		static quarterword rem_byte(int);
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
		GlueSpec *glue; //!< glue specification for interword space, |null| if not allocated
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
		int lig_kern_start(smallnumber) const; //!< beginning of lig/kern program
		int lig_kern_restart(int) const;
		int lig_kern_first(smallnumber) const;
		int char_kern(int) const;
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

inline std::vector<memoryword> Font::info(7);
inline std::vector<Font> fonts(1);
inline internalfontnumber fontinshortdisplay;

Font& cur_font(void);
int curFontNum(void);
int char_tag(fourquarters);
quarterword skip_byte(fourquarters);
quarterword next_char(fourquarters);
quarterword rem_byte(fourquarters);
bool char_exists(fourquarters); 
int& param(smallnumber, internalfontnumber); 
internalfontnumber readfontinfo(halfword, const std::string &, const std::string &, scaled);
[[nodiscard]] int findfontdimen(char, bool);

#endif
