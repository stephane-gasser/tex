#include "scantwentysevenbitint.h"
void scantwentysevenbitint(void)
begin
  scanint;
  if (curval < 0) or (curval > 134217727) then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(696);
    end;
    begin
      helpptr := 2;
      helpline[1] := 697;
      helpline[0] := 689;
    end;
    interror(curval);
    curval := 0;
  end;
end;
