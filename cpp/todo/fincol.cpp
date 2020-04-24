#include "fincol.h"
bool fincol(void)
label
  10;
var
  p: halfword;
  q, r: halfword;
  s: halfword;
  u: halfword;
  w: scaled;
  o: glueord;
  n: halfword;
begin
  if curalign = 0 then
    confusion(908);
  q := mem[curalign].hh.rh;
  if q = 0 then
    confusion(908);
  if alignstate < 500000 then
    fatalerror(595);
  p := mem[q].hh.rh;
  {792:}
if (p = 0) and (mem[curalign + 5].hh.lh < 257) then
    if curloop <> 0 then{793:}

    begin
      mem[q].hh.rh := newnullbox;
      p := mem[q].hh.rh;
      mem[p].hh.lh := 29991;
      mem[p + 1].int := -1073741824;
      curloop := mem[curloop].hh.rh;
      {794:}
q := 29996;
      r := mem[curloop + 3].int;
      while r <> 0 do
      begin
        mem[q].hh.rh := getavail;
        q := mem[q].hh.rh;
        mem[q].hh.lh := mem[r].hh.lh;
        r := mem[r].hh.rh;
      end;
      mem[q].hh.rh := 0;
      mem[p + 3].int := mem[29996].hh.rh;
      q := 29996;
      r := mem[curloop + 2].int;
      while r <> 0 do
      begin
        mem[q].hh.rh := getavail;
        q := mem[q].hh.rh;
        mem[q].hh.lh := mem[r].hh.lh;
        r := mem[r].hh.rh;
      end;
      mem[q].hh.rh := 0;
      mem[p + 2].int := mem[29996].hh.rh{:794}
;
      curloop := mem[curloop].hh.rh;
      mem[p].hh.rh := newglue(mem[curloop + 1].hh.lh);
    end{:793}

    else
    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(909);
      end;
      printesc(898);
      begin
        helpptr := 3;
        helpline[2] := 910;
        helpline[1] := 911;
        helpline[0] := 912;
      end;
      mem[curalign + 5].hh.lh := 257;
      error;
    end{:792}
;
  if mem[curalign + 5].hh.lh <> 256 then
  begin
    unsave;
    newsavelevel(6);
    {796:}
begin
      if curlist.modefield = -102 then
      begin
        adjusttail := curtail;
        u := hpack(mem[curlist.headfield].hh.rh, 0, 1);
        w := mem[u + 1].int;
        curtail := adjusttail;
        adjusttail := 0;
      end
      else
      begin
        u := vpackage(mem[curlist.headfield].hh.rh, 0, 1, 0);
        w := mem[u + 3].int;
      end;
      n := 0;
      if curspan <> curalign then{798:}

      begin
        q := curspan;
        repeat
          n := n + 1;
          q := mem[mem[q].hh.rh].hh.rh;
        until q = curalign;
        if n > 255 then
          confusion(913);
        q := curspan;
        while mem[mem[q].hh.lh].hh.rh < n do
          q := mem[q].hh.lh;
        if mem[mem[q].hh.lh].hh.rh > n then
        begin
          s := getnode(2);
          mem[s].hh.lh := mem[q].hh.lh;
          mem[s].hh.rh := n;
          mem[q].hh.lh := s;
          mem[s + 1].int := w;
        end
        else if mem[mem[q].hh.lh + 1].int < w then
          mem[mem[q].hh.lh + 1].int := w;
      end{:798}

      else if w > mem[curalign + 1].int then
        mem[curalign + 1].int := w;
      mem[u].hh.b0 := 13;
      mem[u].hh.b1 := n;
      {659:}
if totalstretch[3] <> 0 then
        o := 3
      else if totalstretch[2] <> 0 then
        o := 2
      else if totalstretch[1] <> 0 then
        o := 1
      else
        o := 0{:659}
;
      mem[u + 5].hh.b1 := o;
      mem[u + 6].int := totalstretch[o];
      {665:}
if totalshrink[3] <> 0 then
        o := 3
      else if totalshrink[2] <> 0 then
        o := 2
      else if totalshrink[1] <> 0 then
        o := 1
      else
        o := 0{:665}
;
      mem[u + 5].hh.b0 := o;
      mem[u + 4].int := totalshrink[o];
      popnest;
      mem[curlist.tailfield].hh.rh := u;
      curlist.tailfield := u;
    end{:796}
;
    {795:}
begin
      mem[curlist.tailfield].hh.rh := newglue(mem[mem[curalign].hh.rh + 1].hh.lh);
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    mem[curlist.tailfield].hh.b1 := 12{:795}
;
    if mem[curalign + 5].hh.lh >= 257 then
    begin
      fincol := true;
      goto 10;
    end;
    initspan(p);
  end;
  alignstate := 1000000;
  {406:}
repeat
    getxtoken;
  until curcmd <> 10{:406}
;
  curalign := p;
  initcol;
  fincol := false;
  10: ;
end;
