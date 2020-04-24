#include "pushalignment.h"
void pushalignment(void)
var
  p: halfword;
begin
  p := getnode(5);
  mem[p].hh.rh := alignptr;
  mem[p].hh.lh := curalign;
  mem[p + 1].hh.lh := mem[29992].hh.rh;
  mem[p + 1].hh.rh := curspan;
  mem[p + 2].int := curloop;
  mem[p + 3].int := alignstate;
  mem[p + 4].hh.lh := curhead;
  mem[p + 4].hh.rh := curtail;
  alignptr := p;
  curhead := getavail;
end;
