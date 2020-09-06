#ifndef POLICE_H
#define POLICE_H

#include "globals.h"

inline std::vector<memoryword> Font::info(7);
inline std::vector<Font> fonts(1);
inline internalfontnumber fontinshortdisplay;

Font& cur_font(void);
int curFontNum(void);
int char_tag(fourquarters);
quarterword skip_byte(fourquarters);
quarterword next_char(fourquarters);
quarterword op_byte(fourquarters); 
quarterword rem_byte(fourquarters);
bool char_exists(fourquarters); 
int& param(smallnumber, internalfontnumber); 
internalfontnumber readfontinfo(halfword, const std::string &, const std::string &, scaled);
[[nodiscard]] int findfontdimen(bool);

#endif
