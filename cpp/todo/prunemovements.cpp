#include "prunemovements.h"
void prunemovements(int l)
label
  30, 10;
var
  p: halfword;
begin
  while downptr <> 0 do
  begin
    if mem[downptr + 2].int < l then
      goto 30;
    p := downptr;
    downptr := mem[p].hh.rh;
    freenode(p, 3);
  end;
  30:
    while rightptr <> 0 do
    begin
      if mem[rightptr + 2].int < l then
        goto 10;
      p := rightptr;
      rightptr := mem[p].hh.rh;
      freenode(p, 3);
    end;
  10: ;
end;

