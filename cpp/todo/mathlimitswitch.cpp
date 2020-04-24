#include "mathlimitswitch.h"
void mathlimitswitch(void)
label
  10;
begin
  if curlist.headfield <> curlist.tailfield then
    if mem[curlist.tailfield].hh.b0 = 17 then
    begin
      mem[curlist.tailfield].hh.b1 := curchr;
      goto 10;
    end;
  begin
    if interaction = 3 then;
    printnl(262);
    print(1129);
  end;
  begin
    helpptr := 1;
    helpline[0] := 1130;
  end;
  error;
  10: ;
end;
