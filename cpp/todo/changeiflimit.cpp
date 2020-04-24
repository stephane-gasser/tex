#include "changeiflimit.h"
void changeiflimit(smallnumber l, halfword p)
label
  10;
var
  q: halfword;
begin
  if p = condptr then
    iflimit := l
  else
  begin
    q := condptr;
    while true do
    begin
      if q = 0 then
        confusion(756);
      if mem[q].hh.rh = p then
      begin
        mem[q].hh.b0 := l;
        goto 10;
      end;
      q := mem[q].hh.rh;
    end;
  end;
  10: ;
end;
