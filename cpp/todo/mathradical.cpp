#include "mathradical.h"
void mathradical(void)
begin
  begin
    mem[curlist.tailfield].hh.rh := getnode(5);
    curlist.tailfield := mem[curlist.tailfield].hh.rh;
  end;
  mem[curlist.tailfield].hh.b0 := 24;
  mem[curlist.tailfield].hh.b1 := 0;
  mem[curlist.tailfield + 1].hh := emptyfield;
  mem[curlist.tailfield + 3].hh := emptyfield;
  mem[curlist.tailfield + 2].hh := emptyfield;
  scandelimiter(curlist.tailfield + 4, true);
  scanmath(curlist.tailfield + 1);
end;
