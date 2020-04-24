#include "makeover.h"
void makeover(halfword q)
begin
  mem[q + 1].hh.lh := overbar(cleanbox(q + 1, 2 * (curstyle div 2) + 1), 3 * fontinfo[8 + parambase[eqtb[3938 + cursize].hh.rh]].int, fontinfo[8 + parambase[eqtb[3938 + cursize].hh.rh]].int);
  mem[q + 1].hh.rh := 2;
end;
