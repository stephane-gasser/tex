#include "unpackage.h"
void unpackage(void)
label
  10;
var
  p: halfword;
  c: 0..1;
begin
  c := curchr;
  scaneightbitint;
  p := eqtb[3678 + curval].hh.rh;
  if p = 0 then
    goto 10;
  if (abs(curlist.modefield) = 203) or ((abs(curlist.modefield) = 1) and (mem[p].hh.b0 <> 1)) or
    ((abs(curlist.modefield) = 102) and (mem[p].hh.b0 <> 0)) then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(1096);
    end;
    begin
      helpptr := 3;
      helpline[2] := 1097;
      helpline[1] := 1098;
      helpline[0] := 1099;
    end;
    error;
    goto 10;
  end;
  if c = 1 then
    mem[curlist.tailfield].hh.rh := copynodelist(mem[p + 5].hh.rh)
  else
  begin
    mem[curlist.tailfield].hh.rh := mem[p + 5].hh.rh;
    eqtb[3678 + curval].hh.rh := 0;
    freenode(p, 7);
  end;
  while mem[curlist.tailfield].hh.rh <> 0 do
    curlist.tailfield := mem[curlist.tailfield].hh.rh;
  10: ;
end;
