#include "appendpenalty.h"
void appendpenalty(void)
begin
  scanint;
  begin
    mem[curlist.tailfield].hh.rh := newpenalty(curval);
    curlist.tailfield := mem[curlist.tailfield].hh.rh;
  end;
  if curlist.modefield = 1 then
    buildpage;
end;
