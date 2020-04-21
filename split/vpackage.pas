function vpackage(p: halfword; h: scaled; m: smallnumber; l: scaled): halfword;
label
  50, 10;
var
  r: halfword;
  w, d, x: scaled;
  s: scaled;
  g: halfword;
  o: glueord;
begin
  lastbadness := 0;
  r := getnode(7);
  mem[r].hh.b0 := 1;
  mem[r].hh.b1 := 0;
  mem[r + 4].int := 0;
  mem[r + 5].hh.rh := p;
  w := 0;
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
  while p <> 0 do{669:}

  begin
    if (p >= himemmin) then
      confusion(854)
    else
      case mem[p].hh.b0 of
        0, 1, 2, 13:{670:}

        begin
          x := x + d + mem[p + 3].int;
          d := mem[p + 2].int;
          if mem[p].hh.b0 >= 2 then
            s := 0
          else
            s := mem[p + 4].int;
          if mem[p + 1].int + s > w then
            w := mem[p + 1].int + s;
        end{:670}
;
        8:{1359:}
{:1359}
;
        10:{671:}

        begin
          x := x + d;
          d := 0;
          g := mem[p + 1].hh.lh;
          x := x + mem[g + 1].int;
          o := mem[g].hh.b0;
          totalstretch[o] := totalstretch[o] + mem[g + 2].int;
          o := mem[g].hh.b1;
          totalshrink[o] := totalshrink[o] + mem[g + 3].int;
          if mem[p].hh.b1 >= 100 then
          begin
            g := mem[p + 1].hh.rh;
            if mem[g + 1].int > w then
              w := mem[g + 1].int;
          end;
        end{:671}
;
        11:
        begin
          x := x + d + mem[p + 1].int;
          d := 0;
        end;
        others: end;
    p := mem[p].hh.rh;
  end{:669}
;
  mem[r + 1].int := w;
  if d > l then
  begin
    x := x + d - l;
    mem[r + 2].int := l;
  end
  else
    mem[r + 2].int := d;
  {672:}
if m = 1 then
    h := x + h;
  mem[r + 3].int := h;
  x := h - x;
  if x = 0 then
  begin
    mem[r + 5].hh.b0 := 0;
    mem[r + 5].hh.b1 := 0;
    mem[r + 6].gr := 0.0;
    goto 10;
  end
  else if x > 0 then{673:}

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
      if mem[r + 5].hh.rh <> 0 then{674:}

      begin
        lastbadness := badness(x, totalstretch[0]);
        if lastbadness > eqtb[5290].int then
        begin
          println;
          if lastbadness > 100 then
            printnl(843)
          else
            printnl(844);
          print(855);
          printint(lastbadness);
          goto 50;
        end;
      end{:674}
;
    goto 10;
  end{:673}

  else{676:}

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
      {677:}
if (-x - totalshrink[0] > eqtb[5839].int) or (eqtb[5290].int < 100) then
      begin
        println;
        printnl(856);
        printscaled(-x - totalshrink[0]);
        print(857);
        goto 50;
      end{:677}
;
    end
    else if o = 0 then
      if mem[r + 5].hh.rh <> 0 then{678:}

      begin
        lastbadness :=
          badness(-x, totalshrink[0]);
        if lastbadness > eqtb[5290].int then
        begin
          println;
          printnl(858);
          printint(lastbadness);
          goto 50;
        end;
      end{:678}
;
    goto 10;
  end{:676}
{:672}
;
  50:
    {675:}
if outputactive then
      print(846)
    else
    begin
      if packbeginline <> 0 then
      begin
        print(848);
        printint(abs(packbeginline));
        print(849);
      end
      else
        print(850);
      printint(line);
      println;
    end;
  begindiagnostic;
  showbox(r);
  enddiagnostic(true){:675}
;
  10:
    vpackage := r;
end;
