#include "appspace.h"
void appspace(void)
var
  q: halfword;
begin
  if (curlist.auxfield.hh.lh >= 2000) and (eqtb[2895].hh.rh <> 0) then
    q :=
      newparamglue(13)
  else
  begin
    if eqtb[2894].hh.rh <> 0 then
      mainp := eqtb[2894].hh.rh
    else{1042:}

    begin
      mainp := fontglue[eqtb[3934].hh.rh];
      if mainp = 0 then
      begin
        mainp := newspec(0);
        maink := parambase[eqtb[3934].hh.rh] + 2;
        mem[mainp + 1].int := fontinfo[maink].int;
        mem[mainp + 2].int := fontinfo[maink + 1].int;
        mem[mainp + 3].int := fontinfo[maink + 2].int;
        fontglue[eqtb[3934].hh.rh] := mainp;
      end;
    end{:1042}
;
    mainp := newspec(mainp);
    {1044:}
if curlist.auxfield.hh.lh >= 2000 then
      mem[mainp + 1].int := mem[mainp + 1].int + fontinfo[7 + parambase[eqtb[3934].hh.rh]].int;
    mem[mainp + 2].int := xnoverd(mem[mainp + 2].int, curlist.auxfield.hh.lh, 1000);
    mem[mainp + 3].int := xnoverd(mem[mainp + 3].int, 1000, curlist.auxfield.hh.lh)
    {:1044}
;
    q := newglue(mainp);
    mem[mainp].hh.rh := 0;
  end;
  mem[curlist.tailfield].hh.rh := q;
  curlist.tailfield := q;
end;
