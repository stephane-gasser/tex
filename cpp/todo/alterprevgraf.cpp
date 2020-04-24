#include "alterprevgraf.h"
void alterprevgraf(void)
var
  p: 0..nestsize;
begin
  nest[nestptr] := curlist;
  p := nestptr;
  while abs(nest[p].modefield) <> 1 do
    p := p - 1;
  scanoptionalequals;
  scanint;
  if curval < 0 then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(954);
    end;
    printesc(532);
    begin
      helpptr := 1;
      helpline[0] := 1214;
    end;
    interror(curval);
  end
  else
  begin
    nest[p].pgfield := curval;
    curlist := nest[nestptr];
  end;
end;
