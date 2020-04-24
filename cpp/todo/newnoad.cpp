#include "newnoad.h"
halfword newnoad(void)
var
  p: halfword;
begin
  p := getnode(4);
  mem[p].hh.b0 := 16;
  mem[p].hh.b1 := 0;
  mem[p + 1].hh := emptyfield;
  mem[p + 3].hh := emptyfield;
  mem[p + 2].hh := emptyfield;
  newnoad := p;
end;
