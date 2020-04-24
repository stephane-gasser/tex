#include "scandelimiter.h"
void scandelimiter(halfword p, bool r)
begin
  if r then
    scantwentysevenbitint
  else
  begin
    {404:}
repeat
      getxtoken;
    until (curcmd <> 10) and (curcmd <> 0){:404}
;
    case curcmd of
      11, 12: curval := eqtb[5574 + curchr].int;
      15: scantwentysevenbitint;
      others: curval := -1
    end;
  end;
  if curval < 0 then{1161:}

  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(1131);
    end;
    begin
      helpptr := 6;
      helpline[5] := 1132;
      helpline[4] := 1133;
      helpline[3] := 1134;
      helpline[2] := 1135;
      helpline[1] := 1136;
      helpline[0] := 1137;
    end;
    backerror;
    curval := 0;
  end{:1161}
;
  mem[p].qqqq.b0 := (curval div 1048576) mod 16;
  mem[p].qqqq.b1 := (curval div 4096) mod 256 + 0;
  mem[p].qqqq.b2 := (curval div 256) mod 16;
  mem[p].qqqq.b3 := curval mod 256 + 0;
end;
