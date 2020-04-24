#include "appendchoices.h"
void appendchoices(void)
begin
  begin
    mem[curlist.tailfield].hh.rh := newchoice;
    curlist.tailfield := mem[curlist.tailfield].hh.rh;
  end;
  saveptr := saveptr + 1;
  savestack[saveptr - 1].int := 0;
  pushmath(13);
  scanleftbrace;
end;
