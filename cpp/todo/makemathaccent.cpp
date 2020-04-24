#include "makemathaccent.h"
void makemathaccent(halfword q)
label
  30, 31;
var
  p, x, y: halfword;
  a: integer;
  c: quarterword;
  f: internalfontnumber;
  i: fourquarters;
  s: scaled;
  h: scaled;
  delta: scaled;
  w: scaled;
begin
  fetch(q + 4);
  if (curi.b0 > 0) then
  begin
    i := curi;
    c := curc;
    f := curf;
    {741:}
s := 0;
    if mem[q + 1].hh.rh = 1 then
    begin
      fetch(q + 1);
      if ((curi.b2 - 0) mod 4) = 1 then
      begin
        a := ligkernbase[curf] + curi.b3;
        curi := fontinfo[a].qqqq;
        if curi.b0 > 128 then
        begin
          a := ligkernbase[curf] + 256 * curi.b2 + curi.b3 + 32768 - 256 * (128);
          curi := fontinfo[a].qqqq;
        end;
        while true do
        begin
          if curi.b1 - 0 = skewchar[curf] then
          begin
            if curi.b2 >= 128 then
              if curi.b0 <= 128 then
                s := fontinfo[kernbase[curf] + 256 * curi.b2 + curi.b3].int;
            goto 31;
          end;
          if curi.b0 >= 128 then
            goto 31;
          a := a + curi.b0 + 1;
          curi := fontinfo[a].qqqq;
        end;
      end;
    end;
    31:
    {:741}
;
    x := cleanbox(q + 1, 2 * (curstyle div 2) + 1);
    w := mem[x + 1].int;
    h := mem[x + 3].int;
    {740:}
while true do
    begin
      if ((i.b2 - 0) mod 4) <> 2 then
        goto 30;
      y := i.b3;
      i := fontinfo[charbase[f] + y].qqqq;
      if not (i.b0 > 0) then
        goto 30;
      if fontinfo[widthbase[f] + i.b0].int > w then
        goto 30;
      c := y;
    end;
    30:
    {:740}
;
    if h < fontinfo[5 + parambase[f]].int then
      delta := h
    else
      delta := fontinfo[5 + parambase[f]].int;
    if (mem[q + 2].hh.rh <> 0) or (mem[q + 3].hh.rh <> 0) then
      if mem[q + 1].hh.rh = 1 then
        {742:}
begin
        flushnodelist(x);
        x := newnoad;
        mem[x + 1] := mem[q + 1];
        mem[x + 2] := mem[q + 2];
        mem[x + 3] := mem[q + 3];
        mem[q + 2].hh := emptyfield;
        mem[q + 3].hh := emptyfield;
        mem[q + 1].hh.rh := 3;
        mem[q + 1].hh.lh := x;
        x := cleanbox(q + 1, curstyle);
        delta := delta + mem[x + 3].int - h;
        h := mem[x + 3].int;
      end{:742}
;
    y := charbox(f, c);
    mem[y + 4].int := s + half(w - mem[y + 1].int);
    mem[y + 1].int := 0;
    p := newkern(-delta);
    mem[p].hh.rh := x;
    mem[y].hh.rh := p;
    y := vpackage(y, 0, 1, 1073741823);
    mem[y + 1].int := mem[x + 1].int;
    if mem[y + 3].int < h then{739:}

    begin
      p := newkern(h - mem[y + 3].int);
      mem[p].hh.rh := mem[y + 5].hh.rh;
      mem[y + 5].hh.rh := p;
      mem[y + 3].int := h;
    end{:739}
;
    mem[q + 1].hh.lh := y;
    mem[q + 1].hh.rh := 2;
  end;
end;

