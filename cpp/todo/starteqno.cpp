#include "starteqno.h"
void starteqno(void)
begin
  savestack[saveptr + 0].int := curchr;
  saveptr := saveptr + 1;
  {1139:}
begin
    pushmath(15);
    eqworddefine(5307, -1);
    if eqtb[3415].hh.rh <> 0 then
      begintokenlist(eqtb[3415].hh.rh, 8);
  end{:1139}
;
end;
