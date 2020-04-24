#include "newwhatsit.h"
void newwhatsit(smallnumber s, smallnumber w)
var
  p: halfword;
begin
  p := getnode(w);
  mem[p].hh.b0 := 8;
  mem[p].hh.b1 := s;
  mem[curlist.tailfield].hh.rh := p;
  curlist.tailfield := p;
end;
