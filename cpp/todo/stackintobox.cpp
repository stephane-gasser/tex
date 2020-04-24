#include "stackintobox.h"
void stackintobox(halfword b, internalfontnumber f, quarterword c)
var
  p: halfword;
begin
  p := charbox(f, c);
  mem[p].hh.rh := mem[b + 5].hh.rh;
  mem[b + 5].hh.rh := p;
  mem[b + 3].int := mem[p + 3].int;
end;
