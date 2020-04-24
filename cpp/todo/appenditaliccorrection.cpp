#include "appenditaliccorrection.h"
void appenditaliccorrection(void)
label
  10;
var
  p: halfword;
  f: internalfontnumber;
begin
  if curlist.tailfield <> curlist.headfield then
  begin
    if (curlist.tailfield >= himemmin) then
      p := curlist.tailfield
    else if mem[curlist.tailfield].hh.b0 = 6 then
      p := curlist.tailfield + 1
    else
      goto 10;
    f := mem[p].hh.b0;
    begin
      mem[curlist.tailfield].hh.rh := newkern(fontinfo[italicbase[f] + (fontinfo[charbase[f] + mem[p].hh.b1].qqqq.b2 - 0) div 4].int);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    mem[curlist.tailfield].hh.b1 := 1;
  end;
  10: ;
end;
