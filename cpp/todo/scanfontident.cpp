#include "scanfontident.h"
void scanfontident(void)
var
  f: internalfontnumber;
  m: halfword;
begin
  {406:}
repeat
    getxtoken;
  until curcmd <> 10{:406}
;
  if curcmd = 88 then
    f := eqtb[3934].hh.rh
  else if curcmd = 87 then
    f := curchr
  else if curcmd = 86 then
  begin
    m := curchr;
    scanfourbitint;
    f := eqtb[m + curval].hh.rh;
  end
  else
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(816);
    end;
    begin
      helpptr := 2;
      helpline[1] := 817;
      helpline[0] := 818;
    end;
    backerror;
    f := 0;
  end;
  curval := f;
end;
