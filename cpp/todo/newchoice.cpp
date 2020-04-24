#include "newchoice.h"
halfword newchoice(void)
var
  p: halfword;
begin
  p := getnode(3);
  mem[p].hh.b0 := 15;
  mem[p].hh.b1 := 0;
  mem[p + 1].hh.lh := 0;
  mem[p + 1].hh.rh := 0;
  mem[p + 2].hh.lh := 0;
  mem[p + 2].hh.rh := 0;
  newchoice := p;
end;
