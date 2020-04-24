#include "headforvmode.h"
void headforvmode(void)
begin
  if curlist.modefield < 0 then
    if curcmd <> 36 then
      offsave
    else
    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(685);
      end;
      printesc(521);
      print(1081);
      begin
        helpptr := 2;
        helpline[1] := 1082;
        helpline[0] := 1083;
      end;
      error;
    end
  else
  begin
    backinput;
    curtok := partoken;
    backinput;
    curinput.indexfield := 4;
  end;
end;
