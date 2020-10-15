#ifndef MAINLOOP_H
#define MAINLOOP_H

#include "globals.h"
#include "token.h"

inline bool cancelboundary = false;

void main_loop(char, Token&);
void appspace(void);
[[nodiscard]] Token append_normal_space(char);

#endif
