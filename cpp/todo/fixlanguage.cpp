#include "fixlanguage.h"
void fixlanguage(void)
var
  l: ASCIIcode;
begin
  if eqtb[5313].int <= 0 then
    l := 0
  else if eqtb[5313].int > 255 then
    l :=
      0
  else
    l := eqtb[5313].int;
  if l <> curlist.auxfield.hh.rh then
  begin
    newwhatsit(4, 2);
    mem[curlist.tailfield + 1].hh.rh := l;
    curlist.auxfield.hh.rh := l;
    mem[curlist.tailfield + 1].hh.b0 := normmin(eqtb[5314].int);
    mem[curlist.tailfield + 1].hh.b1 := normmin(eqtb[5315].int);
  end;
end;
