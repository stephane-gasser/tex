#include "scanfifteenbitint.h"
void scanfifteenbitint(void)
begin
  scanint;
  if (curval < 0) or (curval > 32767) then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(694);
    end;
    begin
      helpptr := 2;
      helpline[1] := 695;
      helpline[0] := 689;
    end;
    interror(curval);
    curval := 0;
  end;
end;
