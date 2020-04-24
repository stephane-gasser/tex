#include "scankeyword.h"
bool scankeyword(strnumber s)
label
  10;
var
  p: halfword;
  q: halfword;
  k: poolpointer;
begin
  p := 29987;
  mem[p].hh.rh := 0;
  k := strstart[s];
  while k < strstart[s + 1] do
  begin
    getxtoken;
    if (curcs = 0) and ((curchr = strpool[k]) or (curchr = strpool[k] - 32)) then
    begin
      begin
        q := getavail;
        mem[p].hh.rh := q;
        mem[q].hh.lh := curtok;
        p := q;
      end;
      k := k + 1;
    end
    else if (curcmd <> 10) or (p <> 29987) then
    begin
      backinput;
      if p <> 29987 then
        begintokenlist(mem[29987].hh.rh, 3);
      scankeyword := false;
      goto 10;
    end;
  end;
  flushlist(mem[29987].hh.rh);
  scankeyword := true;
  10: ;
end;
