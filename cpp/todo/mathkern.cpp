#include "mathkern.h"
void mathkern(halfword p, scaled m)
var
  n: integer;
  f: scaled;
begin
  if mem[p].hh.b1 = 99 then
  begin
    n := xovern(m, 65536);
    f := remainder;
    if f < 0 then
    begin
      n := n - 1;
      f := f + 65536;
    end;
    mem[p + 1].int := multandadd(n, mem[p + 1].int, xnoverd(mem[p + 1].int, f, 65536), 1073741823);
    mem[p].hh.b1 := 1;
  end;
end;
