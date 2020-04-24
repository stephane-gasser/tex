#include "vardelimiter.h"
halfword vardelimiter(halfword d, smallnumber s, scaled v)
label
  40, 22;
var
  b: halfword;
  f, g: internalfontnumber;
  c, x, y: quarterword;
  m, n: integer;
  u: scaled;
  w: scaled;
  q: fourquarters;
  hd: eightbits;
  r: fourquarters;
  z: smallnumber;
  largeattempt: boolean;
begin
  f := 0;
  w := 0;
  largeattempt := false;
  z := mem[d].qqqq.b0;
  x := mem[d].qqqq.b1;
  while true do
  begin
    {707:}
if (z <> 0) or (x <> 0) then
    begin
      z := z + s + 16;
      repeat
        z := z - 16;
        g := eqtb[3935 + z].hh.rh;
        if g <> 0 then{708:}

        begin
          y := x;
          if (y - 0 >= fontbc[g]) and (y - 0 <= fontec[g]) then
          begin
            22:
              q := fontinfo[charbase[g] + y].qqqq;
            if (q.b0 > 0) then
            begin
              if ((q.b2 - 0) mod 4) = 3 then
              begin
                f := g;
                c := y;
                goto 40;
              end;
              hd := q.b1 - 0;
              u := fontinfo[heightbase[g] + (hd) div 16].int + fontinfo[depthbase[g] + (hd) mod 16].int;
              if u > w then
              begin
                f := g;
                c := y;
                w := u;
                if u >= v then
                  goto 40;
              end;
              if ((q.b2 - 0) mod 4) = 2 then
              begin
                y := q.b3;
                goto 22;
              end;
            end;
          end;
        end{:708}
;
      until z < 16;
    end{:707}
;
    if largeattempt then
      goto 40;
    largeattempt := true;
    z := mem[d].qqqq.b2;
    x := mem[d].qqqq.b3;
  end;
  40:
    if f <> 0 then
      {710:}
if ((q.b2 - 0) mod 4) = 3 then{713:}

      begin
        b := newnullbox;
        mem[b].hh.b0 := 1;
        r := fontinfo[extenbase[f] + q.b3].qqqq;
        {714:}
c := r.b3;
        u := heightplusdepth(f, c);
        w := 0;
        q := fontinfo[charbase[f] + c].qqqq;
        mem[b + 1].int := fontinfo[widthbase[f] + q.b0].int + fontinfo[italicbase[f] + (q.b2 - 0) div 4].int;
        c := r.b2;
        if c <> 0 then
          w := w + heightplusdepth(f, c);
        c := r.b1;
        if c <> 0 then
          w := w + heightplusdepth(f, c);
        c := r.b0;
        if c <> 0 then
          w := w + heightplusdepth(f, c);
        n := 0;
        if u > 0 then
          while w < v do
          begin
            w := w + u;
            n := n + 1;
            if r.b1 <> 0 then
              w := w + u;
          end{:714}
;
        c := r.b2;
        if c <> 0 then
          stackintobox(b, f, c);
        c := r.b3;
        for m := 1 to n do
          stackintobox(b, f, c);
        c := r.b1;
        if c <> 0 then
        begin
          stackintobox(b, f, c);
          c := r.b3;
          for m := 1 to n do
            stackintobox(b, f, c);
        end;
        c := r.b0;
        if c <> 0 then
          stackintobox(b, f, c);
        mem[b + 2].int := w - mem[b + 3].int;
      end{:713}

      else
        b := charbox(f, c){:710}

    else
    begin
      b := newnullbox;
      mem[b + 1].int := eqtb[5841].int;
    end;
  mem[b + 4].int := half(mem[b + 3].int - mem[b + 2].int) - fontinfo[22 + parambase[eqtb[3937 + s].hh.rh]].int;
  vardelimiter := b;
end;
