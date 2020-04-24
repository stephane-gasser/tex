#include "buildpage.h"
void buildpage(void)
label
  10, 30, 31, 22, 80, 90;
var
  p: halfword;
  q, r: halfword;
  b, c: integer;
  pi: integer;
  n: 0..255;
  delta, h, w: scaled;
begin
  if (mem[29999].hh.rh = 0) or outputactive then
    goto 10;
  repeat
    22:
      p := mem[29999].hh.rh;
    {996:}
if lastglue <> 65535 then
      deleteglueref(lastglue);
    lastpenalty := 0;
    lastkern := 0;
    if mem[p].hh.b0 = 10 then
    begin
      lastglue := mem[p + 1].hh.lh;
      mem[lastglue].hh.rh := mem[lastglue].hh.rh + 1;
    end
    else
    begin
      lastglue := 65535;
      if mem[p].hh.b0 = 12 then
        lastpenalty := mem[p + 1].int
      else if mem[p].hh.b0 = 11 then
        lastkern := mem[p + 1].int;
    end{:996}
;
    {997:}
{1000:}
case mem[p].hh.b0 of
      0, 1, 2: if pagecontents < 2 then{1001:}

        begin
          if pagecontents = 0 then
            freezepagespecs(2)
          else
            pagecontents := 2;
          q := newskipparam(9);
          if mem[tempptr + 1].int > mem[p + 3].int then
            mem[tempptr + 1].int := mem[tempptr + 1].int - mem[p + 3].int
          else
            mem[tempptr + 1].int := 0;
          mem[q].hh.rh := p;
          mem[29999].hh.rh := q;
          goto 22;
        end{:1001}

        else{1002:}

        begin
          pagesofar[1] := pagesofar[1] + pagesofar[7] + mem[p + 3].int;
          pagesofar[7] := mem[p + 2].int;
          goto 80;
        end{:1002}
;
      8:{1364:}
goto 80{:1364}
;
      10: if pagecontents < 2 then
          goto 31
        else if (mem[pagetail].hh.b0 < 9) then
          pi := 0
        else
          goto 90;
      11: if pagecontents < 2 then
          goto 31
        else if mem[p].hh.rh = 0 then
          goto 10
        else if mem[mem[p].hh.rh].hh.b0 = 10 then
          pi := 0
        else
          goto 90;
      12: if pagecontents < 2 then
          goto 31
        else
          pi := mem[p + 1].int;
      4: goto 80;
      3:{1008:}

      begin
        if pagecontents = 0 then
          freezepagespecs(1);
        n := mem[p].hh.b1;
        r := 30000;
        while n >= mem[mem[r].hh.rh].hh.b1 do
          r := mem[r].hh.rh;
        n := n - 0;
        if mem[r].hh.b1 <> n + 0 then{1009:}

        begin
          q := getnode(4);
          mem[q].hh.rh := mem[r].hh.rh;
          mem[r].hh.rh := q;
          r := q;
          mem[r].hh.b1 := n + 0;
          mem[r].hh.b0 := 0;
          ensurevbox(n);
          if eqtb[3678 + n].hh.rh = 0 then
            mem[r + 3].int := 0
          else
            mem[r + 3].int := mem[eqtb[3678 + n].hh.rh + 3].int + mem[eqtb[3678 + n].hh.rh + 2].int;
          mem[r + 2].hh.lh := 0;
          q := eqtb[2900 + n].hh.rh;
          if eqtb[5318 + n].int = 1000 then
            h := mem[r + 3].int
          else
            h := xovern(mem[r + 3].int, 1000) * eqtb[5318 + n].int;
          pagesofar[0] := pagesofar[0] - h - mem[q + 1].int;
          pagesofar[2 + mem[q].hh.b0] := pagesofar[2 + mem[q].hh.b0] + mem[q + 2].int;
          pagesofar[6] := pagesofar[6] + mem[q + 3].int;
          if (mem[q].hh.b1 <> 0) and (mem[q + 3].int <> 0) then
          begin
            begin
              if interaction = 3 then;
              printnl(262);
              print(997);
            end;
            printesc(395);
            printint(n);
            begin
              helpptr := 3;
              helpline[2] := 998;
              helpline[1] := 999;
              helpline[0] := 921;
            end;
            error;
          end;
        end{:1009}
;
        if mem[r].hh.b0 = 1 then
          insertpenalties := insertpenalties + mem[p + 1].int
        else
        begin
          mem[r + 2].hh.rh := p;
          delta := pagesofar[0] - pagesofar[1] - pagesofar[7] + pagesofar[6];
          if eqtb[5318 + n].int = 1000 then
            h := mem[p + 3].int
          else
            h := xovern(mem[p + 3].int, 1000) * eqtb[5318 + n].int;
          if ((h <= 0) or (h <= delta)) and (mem[p + 3].int + mem[r + 3].int <= eqtb[5851 + n].int) then
          begin
            pagesofar[0] := pagesofar[0] - h;
            mem[r + 3].int := mem[r + 3].int + mem[p + 3].int;
          end
          else{1010:}

          begin
            if eqtb[5318 + n].int <= 0 then
              w := 1073741823
            else
            begin
              w := pagesofar[0] - pagesofar[1] - pagesofar[7];
              if eqtb[5318 + n].int <> 1000 then
                w := xovern(w, eqtb[5318 + n].int) * 1000;
            end;
            if w > eqtb[5851 + n].int - mem[r + 3].int then
              w := eqtb[5851 + n].int - mem[r + 3].int;
            q := vertbreak(mem[p + 4].hh.lh, w, mem[p + 2].int);
            mem[r + 3].int := mem[r + 3].int + bestheightplusdepth;
{if eqtb[5296].int>0 then[1011:]begin begindiagnostic;printnl(1000);
printint(n);print(1001);printscaled(w);printchar(44);
printscaled(bestheightplusdepth);print(930);
if q=0 then printint(-10000)else if mem[q].hh.b0=12 then printint(mem[q
+1].int)else printchar(48);enddiagnostic(false);end[:1011];}

            if eqtb[5318 + n].int <> 1000 then
              bestheightplusdepth := xovern(bestheightplusdepth, 1000) * eqtb[5318 + n].int;
            pagesofar[0] := pagesofar[0] - bestheightplusdepth;
            mem[r].hh.b0 := 1;
            mem[r + 1].hh.rh := q;
            mem[r + 1].hh.lh := p;
            if q = 0 then
              insertpenalties := insertpenalties - 10000
            else if mem[q].hh.b0 = 12 then
              insertpenalties := insertpenalties + mem[q + 1].int;
          end{:1010}
;
        end;
        goto 80;
      end{:1008}
;
      others: confusion(992)
    end{:1000}
;
    {1005:}
if pi < 10000 then
    begin
      {1007:}
if pagesofar[1] < pagesofar[0] then
        if (pagesofar[3] <> 0) or (pagesofar[4] <> 0) or (pagesofar[5] <> 0) then
          b := 0
        else
          b :=
            badness(pagesofar[0] - pagesofar[1], pagesofar[2])
      else if pagesofar[1] - pagesofar[0] > pagesofar[6] then
        b := 1073741823
      else
        b := badness(pagesofar[1] - pagesofar[0], pagesofar[6]){:1007}
;
      if b < 1073741823 then
        if pi <= -10000 then
          c := pi
        else if b < 10000 then
          c := b + pi + insertpenalties
        else
          c := 100000
      else
        c := b;
      if insertpenalties >= 10000 then
        c := 1073741823;
{if eqtb[5296].int>0 then[1006:]begin begindiagnostic;printnl(37);
print(926);printtotals;print(995);printscaled(pagesofar[0]);print(929);
if b=1073741823 then printchar(42)else printint(b);print(930);
printint(pi);print(996);
if c=1073741823 then printchar(42)else printint(c);
if c<=leastpagecost then printchar(35);enddiagnostic(false);end[:1006];}

      if c <= leastpagecost then
      begin
        bestpagebreak := p;
        bestsize := pagesofar[0];
        leastpagecost := c;
        r := mem[30000].hh.rh;
        while r <> 30000 do
        begin
          mem[r + 2].hh.lh := mem[r + 2].hh.rh;
          r := mem[r].hh.rh;
        end;
      end;
      if (c = 1073741823) or (pi <= -10000) then
      begin
        fireup(p);
        if outputactive then
          goto 10;
        goto 30;
      end;
    end{:1005}
;
    if (mem[p].hh.b0 < 10) or (mem[p].hh.b0 > 11) then
      goto 80;
    90:
      {1004:}
if mem[p].hh.b0 = 11 then
        q := p
      else
      begin
        q := mem[p + 1].hh.lh;
        pagesofar[2 + mem[q].hh.b0] := pagesofar[2 + mem[q].hh.b0] + mem[q + 2].int;
        pagesofar[6] := pagesofar[6] + mem[q + 3].int;
        if (mem[q].hh.b1 <> 0) and (mem[q + 3].int <> 0) then
        begin
          begin
            if interaction = 3 then;
            printnl(262);
            print(993);
          end;
          begin
            helpptr := 4;
            helpline[3] := 994;
            helpline[2] := 962;
            helpline[1] := 963;
            helpline[0] := 921;
          end;
          error;
          r := newspec(q);
          mem[r].hh.b1 := 0;
          deleteglueref(q);
          mem[p + 1].hh.lh := r;
          q := r;
        end;
      end;
    pagesofar[1] := pagesofar[1] + pagesofar[7] + mem[q + 1].int;
    pagesofar[7] := 0{:1004}
;
    80:
      {1003:}
if pagesofar[7] > pagemaxdepth then
      begin
        pagesofar[1] :=
          pagesofar[1] + pagesofar[7] - pagemaxdepth;
        pagesofar[7] := pagemaxdepth;
      end;
    {:1003}
;
    {998:}
mem[pagetail].hh.rh := p;
    pagetail := p;
    mem[29999].hh.rh := mem[p].hh.rh;
    mem[p].hh.rh := 0;
    goto 30{:998}
;
    31:
      {999:}
mem[29999].hh.rh := mem[p].hh.rh;
    mem[p].hh.rh := 0;
    flushnodelist(p){:999}
;
    30:
    {:997}
;
  until mem[29999].hh.rh = 0;
  {995:}
if nestptr = 0 then
    curlist.tailfield := 29999
  else
    nest[0].tailfield := 29999{:995}
;
  10: ;
end;
