#include "initcol.h"
void initcol(void)
begin
  mem[curalign + 5].hh.lh := curcmd;
  if curcmd = 63 then
    alignstate := 0
  else
  begin
    backinput;
    begintokenlist(mem[curalign + 3].int, 1);
  end;
end;
