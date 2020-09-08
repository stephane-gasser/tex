#ifndef MAINLOOP_H
#define MAINLOOP_H

#include "globals.h"

inline bool cancelboundary = false;

void main_loop(Token&);
void appspace(void);
[[nodiscard]] Token append_normal_space(void);

#endif
