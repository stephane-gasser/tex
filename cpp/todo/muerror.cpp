#include "muerror.h"
void muerror(void)
begin
  begin
    if interaction = 3 then;
    printnl(262);
    print(662);
  end;
  begin
    helpptr := 1;
    helpline[0] := 663;
  end;
  error;
end;
