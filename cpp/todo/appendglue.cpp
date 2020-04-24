#include "appendglue.h"
void appendglue(void)
var
  s: smallnumber;
begin
  s := curchr;
  case s of
    0: curval := 4;
    1: curval := 8;
    2: curval := 12;
    3: curval := 16;
    4: scanglue(2);
    5: scanglue(3);
  end;
  begin
    mem[curlist.tailfield].hh.rh := newglue(curval);
    curlist.tailfield := mem[curlist.tailfield].hh.rh;
  end;
  if s >= 4 then
  begin
    mem[curval].hh.rh := mem[curval].hh.rh - 1;
    if s > 4 then
      mem[curlist.tailfield].hh.b1 := 99;
  end;
end;
