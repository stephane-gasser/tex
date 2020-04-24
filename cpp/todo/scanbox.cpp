#include "scanbox.h"
void scanbox(int boxcontext)
begin
  {404:}
repeat
    getxtoken;
  until (curcmd <> 10) and (curcmd <> 0){:404}
;
  if curcmd = 20 then
    beginbox(boxcontext)
  else if (boxcontext >= 1073742337) and ((curcmd = 36) or (curcmd = 35)) then
  begin
    curbox := scanrulespec;
    boxend(boxcontext);
  end
  else
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(1075);
    end;
    begin
      helpptr := 3;
      helpline[2] := 1076;
      helpline[1] := 1077;
      helpline[0] := 1078;
    end;
    backerror;
  end;
end;
