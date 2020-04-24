#include "hpack.h"
halfword hpack(halfword p, scaled w, smallnumber m)
label
  21, 50, 10;
var
  r: halfword;
  q: halfword;
  h, d, x: scaled;
  s: scaled;
  g: halfword;
  o: glueord;
  f: internalfontnumber;
  i: fourquarters;
  hd: eightbits;
begin
  lastbadness := 0;
  r := getnode(7);
  mem[r].hh.b0 := 0;
  mem[r].hh.b1 := 0;
  mem[r + 4].int := 0;
  q := r + 5;
  mem[q].hh.rh := p;
  h := 0;
  {650:}
d := 0;
  x := 0;
  totalstretch[0] := 0;
  totalshrink[0] := 0;
  totalstretch[1] := 0;
  totalshrink[1] := 0;
  totalstretch[2] := 0;
  totalshrink[2] := 0;
  totalstretch[3] := 0;
  totalshrink[3] := 0{:650}
;
  while p <> 0 do{651:}

  begin
    21:
      while (p >= himemmin) do{654:}

      begin
        f := mem[p].hh.b0;
        i := fontinfo[charbase[f] + mem[p].hh.b1].qqqq;
        hd := i.b1 - 0;
        x := x + fontinfo[widthbase[f] + i.b0].int;
        s := fontinfo[heightbase[f] + (hd) div 16].int;
        if s > h then
          h := s;
        s := fontinfo[depthbase[f] + (hd) mod 16].int;
        if s > d then
          d := s;
        p := mem[p].hh.rh;
      end{:654}
;
    if p <> 0 then
    begin
      case mem[p].hh.b0 of
        0, 1, 2, 13:{653:}

        begin
          x := x + mem[p + 1].int;
          if mem[p].hh.b0 >= 2 then
            s := 0
          else
            s := mem[p + 4].int;
          if mem[p + 3].int - s > h then
            h := mem[p + 3].int - s;
          if mem[p + 2].int + s > d then
            d := mem[p + 2].int + s;
        end{:653}
;
        3, 4, 5: if adjusttail <> 0 then{655:}

          begin
            while mem[q].hh.rh <> p do
              q := mem[q].hh.rh;
            if mem[p].hh.b0 = 5 then
            begin
              mem[adjusttail].hh.rh := mem[p + 1].int;
              while mem[adjusttail].hh.rh <> 0 do
                adjusttail := mem[adjusttail].hh.rh;
              p := mem[p].hh.rh;
              freenode(mem[q].hh.rh, 2);
            end
            else
            begin
              mem[adjusttail].hh.rh := p;
              adjusttail := p;
              p := mem[p].hh.rh;
            end;
            mem[q].hh.rh := p;
            p := q;
          end{:655}
;
        8:{1360:}
{:1360}
;
        10:{656:}

        begin
          g := mem[p + 1].hh.lh;
          x := x + mem[g + 1].int;
          o := mem[g].hh.b0;
          totalstretch[o] := totalstretch[o] + mem[g + 2].int;
          o := mem[g].hh.b1;
          totalshrink[o] := totalshrink[o] + mem[g + 3].int;
          if mem[p].hh.b1 >= 100 then
          begin
            g := mem[p + 1].hh.rh;
            if mem[g + 3].int > h then
              h := mem[g + 3].int;
            if mem[g + 2].int > d then
              d := mem[g + 2].int;
          end;
        end{:656}
;
        11, 9: x := x + mem[p + 1].int;
        6:{652:}

        begin
          mem[29988] := mem[p + 1];
          mem[29988].hh.rh := mem[p].hh.rh;
          p := 29988;
          goto 21;
        end{:652}
;
        others: end;
      p := mem[p].hh.rh;
    end;
  end{:651}
;
  if adjusttail <> 0 then
    mem[adjusttail].hh.rh := 0;
  mem[r + 3].int := h;
  mem[r + 2].int := d;
  {657:}
if m = 1 then
    w := x + w;
  mem[r + 1].int := w;
  x := w - x;
  if x = 0 then
  begin
    mem[r + 5].hh.b0 := 0;
    mem[r + 5].hh.b1 := 0;
    mem[r + 6].gr := 0.0;
    goto 10;
  end
  else if x > 0 then{658:}

  begin
    {659:}
if totalstretch[3] <> 0 then
      o := 3
    else if totalstretch[2] <> 0 then
      o := 2
    else if totalstretch[1] <> 0 then
      o :=
        1
    else
      o := 0{:659}
;
    mem[r + 5].hh.b1 := o;
    mem[r + 5].hh.b0 := 1;
    if totalstretch[o] <> 0 then
      mem[r + 6].gr := x / totalstretch[o]
    else
    begin
      mem[
        r + 5].hh.b0 := 0;
      mem[r + 6].gr := 0.0;
    end;
    if o = 0 then
      if mem[r + 5].hh.rh <> 0 then{660:}

      begin
        lastbadness := badness(x, totalstretch[0]);
        if lastbadness > eqtb[5289].int then
        begin
          println;
          if lastbadness > 100 then
            printnl(843)
          else
            printnl(844);
          print(845);
          printint(lastbadness);
          goto 50;
        end;
      end{:660}
;
    goto 10;
  end{:658}

  else{664:}

  begin
    {665:}
if totalshrink[3] <> 0 then
      o := 3
    else if totalshrink[2] <> 0 then
      o := 2
    else if totalshrink[1] <> 0 then
      o := 1
    else
      o :=
        0{:665}
;
    mem[r + 5].hh.b1 := o;
    mem[r + 5].hh.b0 := 2;
    if totalshrink[o] <> 0 then
      mem[r + 6].gr := (-x) / totalshrink[o]
    else
    begin
      mem
        [r + 5].hh.b0 := 0;
      mem[r + 6].gr := 0.0;
    end;
    if (totalshrink[o] < -x) and (o = 0) and (mem[r + 5].hh.rh <> 0) then
    begin
      lastbadness := 1000000;
      mem[r + 6].gr := 1.0;
      {666:}
if (-x - totalshrink[0] > eqtb[5838].int) or (eqtb[5289].int < 100) then
      begin
        if (eqtb[5846].int > 0) and (-x - totalshrink[0] > eqtb[5838].int) then
        begin
          while mem[q].hh.rh <> 0 do
            q := mem[q].hh.rh;
          mem[q].hh.rh := newrule;
          mem[mem[q].hh.rh + 1].int := eqtb[5846].int;
        end;
        println;
        printnl(851);
        printscaled(-x - totalshrink[0]);
        print(852);
        goto 50;
      end{:666}
;
    end
    else if o = 0 then
      if mem[r + 5].hh.rh <> 0 then{667:}

      begin
        lastbadness :=
          badness(-x, totalshrink[0]);
        if lastbadness > eqtb[5289].int then
        begin
          println;
          printnl(853);
          printint(lastbadness);
          goto 50;
        end;
      end{:667}
;
    goto 10;
  end{:664}
{:657}
;
  50:
    {663:}
if outputactive then
      print(846)
    else
    begin
      if packbeginline <> 0 then
      begin
        if packbeginline > 0 then
          print(847)
        else
          print(848);
        printint(abs(packbeginline));
        print(849);
      end
      else
        print(850);
      printint(line);
    end;
  println;
  fontinshortdisplay := 0;
  shortdisplay(mem[r + 5].hh.rh);
  println;
  begindiagnostic;
  showbox(r);
  enddiagnostic(true){:663}
;
  10:
    hpack := r;
end;
