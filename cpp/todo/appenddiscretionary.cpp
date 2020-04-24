#include "appenddiscretionary.h"
void appenddiscretionary(void)
var
  c: integer;
begin
  begin
    mem[curlist.tailfield].hh.rh := newdisc;
    curlist.tailfield := mem[curlist.tailfield].hh.rh;
  end;
  if curchr = 1 then
  begin
    c := hyphenchar[eqtb[3934].hh.rh];
    if c >= 0 then
      if c < 256 then
        mem[curlist.tailfield + 1].hh.lh := newcharacter(eqtb[3934].hh.rh, c);
  end
  else
  begin
    saveptr := saveptr + 1;
    savestack[saveptr - 1].int := 0;
    newsavelevel(10);
    scanleftbrace;
    pushnest;
    curlist.modefield := -102;
    curlist.auxfield.hh.lh := 1000;
  end;
end;
