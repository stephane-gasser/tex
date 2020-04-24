#include "ensurevbox.h"
void ensurevbox(eightbits n)
var
  p: halfword;
begin
  p := eqtb[3678 + n].hh.rh;
  if p <> 0 then
    if mem[p].hh.b0 = 0 then
    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(988);
      end;
      begin
        helpptr := 3;
        helpline[2] := 989;
        helpline[1] := 990;
        helpline[0] := 991;
      end;
      boxerror(n);
    end;
end;
