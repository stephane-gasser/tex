#include "mathleftright.h"
void mathleftright(void)
var
  t: smallnumber;
  p: halfword;
begin
  t := curchr;
  if (t = 31) and (curgroup <> 16) then{1192:}

  begin
    if curgroup = 15 then
    begin
      scandelimiter(29988, false);
      begin
        if interaction = 3 then;
        printnl(262);
        print(776);
      end;
      printesc(876);
      begin
        helpptr := 1;
        helpline[0] := 1156;
      end;
      error;
    end
    else
      offsave;
  end{:1192}

  else
  begin
    p := newnoad;
    mem[p].hh.b0 := t;
    scandelimiter(p + 1, false);
    if t = 30 then
    begin
      pushmath(16);
      mem[curlist.headfield].hh.rh := p;
      curlist.tailfield := p;
    end
    else
    begin
      p := finmlist(p);
      unsave;
      begin
        mem[curlist.tailfield].hh.rh := newnoad;
        curlist.tailfield := mem[curlist.tailfield].hh.rh;
      end;
      mem[curlist.tailfield].hh.b0 := 23;
      mem[curlist.tailfield + 1].hh.rh := 3;
      mem[curlist.tailfield + 1].hh.lh := p;
    end;
  end;
end;
