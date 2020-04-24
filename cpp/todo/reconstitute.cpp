#include "reconstitute.h"
smallnumber reconstitute(smallnumber j, smallnumber  n, halfword bchar, halfword  hchar)
label
  22, 30;
var
  p: halfword;
  t: halfword;
  q: fourquarters;
  currh: halfword;
  testchar: halfword;
  w: scaled;
  k: fontindex;
begin
  hyphenpassed := 0;
  t := 29996;
  w := 0;
  mem[29996].hh.rh := 0;
  {908:}
curl := hu[j] + 0;
  curq := t;
  if j = 0 then
  begin
    ligaturepresent := initlig;
    p := initlist;
    if ligaturepresent then
      lfthit := initlft;
    while p > 0 do
    begin
      begin
        mem[t].hh.rh := getavail;
        t := mem[t].hh.rh;
        mem[t].hh.b0 := hf;
        mem[t].hh.b1 := mem[p].hh.b1;
      end;
      p := mem[p].hh.rh;
    end;
  end
  else if curl < 256 then
  begin
    mem[t].hh.rh := getavail;
    t := mem[t].hh.rh;
    mem[t].hh.b0 := hf;
    mem[t].hh.b1 := curl;
  end;
  ligstack := 0;
  begin
    if j < n then
      curr := hu[j + 1] + 0
    else
      curr := bchar;
    if odd(hyf[j]) then
      currh := hchar
    else
      currh := 256;
  end{:908}
;
  22:
    {909:}
if curl = 256 then
    begin
      k := bcharlabel[hf];
      if k = 0 then
        goto 30
      else
        q := fontinfo[k].qqqq;
    end
    else
    begin
      q := fontinfo[charbase[hf] + curl].qqqq;
      if ((q.b2 - 0) mod 4) <> 1 then
        goto 30;
      k := ligkernbase[hf] + q.b3;
      q := fontinfo[k].qqqq;
      if q.b0 > 128 then
      begin
        k := ligkernbase[hf] + 256 * q.b2 + q.b3 + 32768 - 256 * (128);
        q := fontinfo[k].qqqq;
      end;
    end;
  if currh < 256 then
    testchar := currh
  else
    testchar := curr;
  while true do
  begin
    if q.b1 = testchar then
      if q.b0 <= 128 then
        if currh < 256 then
        begin
          hyphenpassed := j;
          hchar := 256;
          currh := 256;
          goto 22;
        end
        else
        begin
          if hchar < 256 then
            if odd(hyf[j]) then
            begin
              hyphenpassed :=
                j;
              hchar := 256;
            end;
          if q.b2 < 128 then{911:}

          begin
            if curl = 256 then
              lfthit := true;
            if j = n then
              if ligstack = 0 then
                rthit := true;
            begin
              if interrupt <> 0 then
                pauseforinstructions;
            end;
            case q.b2 of
              1, 5:
              begin
                curl := q.b3;
                ligaturepresent := true;
              end;
              2, 6:
              begin
                curr := q.b3;
                if ligstack > 0 then
                  mem[ligstack].hh.b1 := curr
                else
                begin
                  ligstack :=
                    newligitem(curr);
                  if j = n then
                    bchar := 256
                  else
                  begin
                    p := getavail;
                    mem[ligstack + 1].hh.rh := p;
                    mem[p].hh.b1 := hu[j + 1] + 0;
                    mem[p].hh.b0 := hf;
                  end;
                end;
              end;
              3:
              begin
                curr := q.b3;
                p := ligstack;
                ligstack := newligitem(curr);
                mem[ligstack].hh.rh := p;
              end;
              7, 11:
              begin
                if ligaturepresent then
                begin
                  p := newligature(hf, curl, mem[curq].hh.rh);
                  if lfthit then
                  begin
                    mem[p].hh.b1 := 2;
                    lfthit := false;
                  end;
                  if false then
                    if ligstack = 0 then
                    begin
                      mem[p].hh.b1 := mem[p].hh.b1 + 1;
                      rthit := false;
                    end;
                  mem[curq].hh.rh := p;
                  t := p;
                  ligaturepresent := false;
                end;
                curq := t;
                curl := q.b3;
                ligaturepresent := true;
              end;
              others:
              begin
                curl := q.b3;
                ligaturepresent := true;
                if ligstack > 0 then
                begin
                  if mem[ligstack + 1].hh.rh > 0 then
                  begin
                    mem[t].hh.rh := mem[ligstack + 1].hh.rh;
                    t := mem[t].hh.rh;
                    j := j + 1;
                  end;
                  p := ligstack;
                  ligstack := mem[p].hh.rh;
                  freenode(p, 2);
                  if ligstack = 0 then
                  begin
                    if j < n then
                      curr := hu[j + 1] + 0
                    else
                      curr := bchar;
                    if odd(hyf[j]) then
                      currh := hchar
                    else
                      currh := 256;
                  end
                  else
                    curr := mem[ligstack].hh.b1;
                end
                else if j = n then
                  goto 30
                else
                begin
                  begin
                    mem[t].hh.rh := getavail;
                    t := mem[t].hh.rh;
                    mem[t].hh.b0 := hf;
                    mem[t].hh.b1 := curr;
                  end;
                  j := j + 1;
                  begin
                    if j < n then
                      curr := hu[j + 1] + 0
                    else
                      curr := bchar;
                    if odd(hyf[j]) then
                      currh := hchar
                    else
                      currh := 256;
                  end;
                end;
              end
            end;
            if q.b2 > 4 then
              if q.b2 <> 7 then
                goto 30;
            goto 22;
          end{:911}
;
          w := fontinfo[kernbase[hf] + 256 * q.b2 + q.b3].int;
          goto 30;
        end;
    if q.b0 >= 128 then
      if currh = 256 then
        goto 30
      else
      begin
        currh := 256;
        goto 22;
      end;
    k := k + q.b0 + 1;
    q := fontinfo[k].qqqq;
  end;
  30:
  {:909}
;
  {910:}
if ligaturepresent then
  begin
    p := newligature(hf, curl, mem[curq].hh.rh);
    if lfthit then
    begin
      mem[p].hh.b1 := 2;
      lfthit := false;
    end;
    if rthit then
      if ligstack = 0 then
      begin
        mem[p].hh.b1 := mem[p].hh.b1 + 1;
        rthit := false;
      end;
    mem[curq].hh.rh := p;
    t := p;
    ligaturepresent := false;
  end;
  if w <> 0 then
  begin
    mem[t].hh.rh := newkern(w);
    t := mem[t].hh.rh;
    w := 0;
  end;
  if ligstack > 0 then
  begin
    curq := t;
    curl := mem[ligstack].hh.b1;
    ligaturepresent := true;
    begin
      if mem[ligstack + 1].hh.rh > 0 then
      begin
        mem[t].hh.rh := mem[ligstack + 1].hh.rh;
        t := mem[t].hh.rh;
        j := j + 1;
      end;
      p := ligstack;
      ligstack := mem[p].hh.rh;
      freenode(p, 2);
      if ligstack = 0 then
      begin
        if j < n then
          curr := hu[j + 1] + 0
        else
          curr := bchar;
        if odd(hyf[j]) then
          currh := hchar
        else
          currh := 256;
      end
      else
        curr := mem[ligstack].hh.b1;
    end;
    goto 22;
  end{:910}
;
  reconstitute := j;
end;
