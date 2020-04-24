#include "vsplit.h"
halfword vsplit(eightbits n, scaled h)
label
  10, 30;
var
  v: halfword;
  p: halfword;
  q: halfword;
begin
  v := eqtb[3678 + n].hh.rh;
  if curmark[3] <> 0 then
  begin
    deletetokenref(curmark[3]);
    curmark[3] := 0;
    deletetokenref(curmark[4]);
    curmark[4] := 0;
  end;
  {978:}
if v = 0 then
  begin
    vsplit := 0;
    goto 10;
  end;
  if mem[v].hh.b0 <> 1 then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(338);
    end;
    printesc(964);
    print(965);
    printesc(966);
    begin
      helpptr := 2;
      helpline[1] := 967;
      helpline[0] := 968;
    end;
    error;
    vsplit := 0;
    goto 10;
  end{:978}
;
  q := vertbreak(mem[v + 5].hh.rh, h, eqtb[5836].int);
  {979:}
p := mem[v + 5].hh.rh;
  if p = q then
    mem[v + 5].hh.rh := 0
  else
    while true do
    begin
      if mem[p].hh.b0 = 4 then
        if curmark[3] = 0 then
        begin
          curmark[3] := mem[p + 1].int;
          curmark[4] := curmark[3];
          mem[curmark[3]].hh.lh := mem[curmark[3]].hh.lh + 2;
        end
        else
        begin
          deletetokenref(curmark[4]);
          curmark[4] := mem[p + 1].int;
          mem[curmark[4]].hh.lh := mem[curmark[4]].hh.lh + 1;
        end;
      if mem[p].hh.rh = q then
      begin
        mem[p].hh.rh := 0;
        goto 30;
      end;
      p := mem[p].hh.rh;
    end;
  30:
  {:979}
;
  q := prunepagetop(q);
  p := mem[v + 5].hh.rh;
  freenode(v, 7);
  if q = 0 then
    eqtb[3678 + n].hh.rh := 0
  else
    eqtb[3678 + n].hh.rh := vpackage(q, 0, 1, 1073741823);
  vsplit := vpackage(p, h, 0, eqtb[5836].int);
  10: ;
end;
