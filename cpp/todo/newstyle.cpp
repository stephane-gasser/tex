#include "newstyle.h"
halfword newstyle(smallnumber s)
var
  p: halfword;
begin
  p := getnode(3);
  mem[p].hh.b0 := 14;
  mem[p].hh.b1 := s;
  mem[p + 1].int := 0;
  mem[p + 2].int := 0;
  newstyle := p;
end;
