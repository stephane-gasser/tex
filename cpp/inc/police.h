#ifndef POLICE_H
#define POLICE_H

#include "globals.h"

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
int& fam_fnt(halfword);
int default_rule_thickness(void); //!< thickness of \\over bars

#endif
