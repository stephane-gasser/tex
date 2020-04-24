#include "mathglue.h"
halfword mathglue(halfword g, scaled m)
var
  p: halfword;
  n: integer;
  f: scaled;
begin
  n := xovern(m, 65536);
  f := remainder;
  if f < 0 then
  begin
    n := n - 1;
    f := f + 65536;
  end;
  p := getnode(4);
  mem[p + 1].int := multandadd(n, mem[g + 1].int, xnoverd(mem[g + 1].int, f, 65536), 1073741823);
  mem[p].hh.b0 := mem[g].hh.b0;
  if mem[p].hh.b0 = 0 then
    mem[p + 2].int := multandadd(n, mem[g + 2].int, xnoverd(mem[g + 2].int, f, 65536), 1073741823)
  else
    mem[p + 2].int := mem[g + 2].int;
  mem[p].hh.b1 := mem[g].hh.b1;
  if mem[p].hh.b1 = 0 then
    mem[p + 3].int := multandadd(n, mem[g + 3].int, xnoverd(mem[g + 3].int, f, 65536), 1073741823)
  else
    mem[p + 3].int := mem[g + 3].int;
  mathglue := p;
end;
