#include "newinteraction.h"
void newinteraction(void)
begin
  println;
  interaction := curchr;
  {75:}
if interaction = 0 then
    selector := 16
  else
    selector := 17{:75}
;
  if logopened then
    selector := selector + 2;
end;
