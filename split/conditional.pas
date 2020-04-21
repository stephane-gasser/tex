procedure conditional;
label
  10, 50;
var
  b: boolean;
  r: 60..62;
  m, n: integer;
  p, q: halfword;
  savescannerstatus: smallnumber;
  savecondptr: halfword;
  thisif: smallnumber;
begin{495:}

  begin
    p := getnode(2);
    mem[p].hh.rh := condptr;
    mem[p].hh.b0 := iflimit;
    mem[p].hh.b1 := curif;
    mem[p + 1].int := ifline;
    condptr := p;
    curif := curchr;
    iflimit := 1;
    ifline := line;
  end{:495}
;
  savecondptr := condptr;
  thisif := curchr;
  {501:}
case thisif of
    0, 1:{506:}

    begin
      begin
        getxtoken;
        if curcmd = 0 then
          if curchr = 257 then
          begin
            curcmd := 13;
            curchr := curtok - 4096;
          end;
      end;
      if (curcmd > 13) or (curchr > 255) then
      begin
        m := 0;
        n := 256;
      end
      else
      begin
        m := curcmd;
        n := curchr;
      end;
      begin
        getxtoken;
        if curcmd = 0 then
          if curchr = 257 then
          begin
            curcmd := 13;
            curchr := curtok - 4096;
          end;
      end;
      if (curcmd > 13) or (curchr > 255) then
      begin
        curcmd := 0;
        curchr := 256;
      end;
      if thisif = 0 then
        b := (n = curchr)
      else
        b := (m = curcmd);
    end{:506}
;
    2, 3:{503:}

    begin
      if thisif = 2 then
        scanint
      else
        scandimen(false, false,
          false);
      n := curval;
      {406:}
repeat
        getxtoken;
      until curcmd <> 10{:406}
;
      if (curtok >= 3132) and (curtok <= 3134) then
        r := curtok - 3072
      else
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(780);
        end;
        printcmdchr(105, thisif);
        begin
          helpptr := 1;
          helpline[0] := 781;
        end;
        backerror;
        r := 61;
      end;
      if thisif = 2 then
        scanint
      else
        scandimen(false, false, false);
      case r of
        60: b := (n < curval);
        61: b := (n = curval);
        62: b := (n > curval);
      end;
    end{:503}
;
    4:{504:}

    begin
      scanint;
      b := odd(curval);
    end{:504}
;
    5: b := (abs(curlist.modefield) = 1);
    6: b := (abs(curlist.modefield) = 102);
    7: b := (abs(curlist.modefield) = 203);
    8: b := (curlist.modefield < 0);
    9, 10, 11:{505:}

    begin
      scaneightbitint;
      p := eqtb[3678 + curval].hh.rh;
      if thisif = 9 then
        b := (p = 0)
      else if p = 0 then
        b := false
      else if thisif = 10 then
        b := (mem[p].hh.b0 = 0)
      else
        b := (mem[p].hh.b0 = 1);
    end{:505}
;
    12:{507:}

    begin
      savescannerstatus := scannerstatus;
      scannerstatus := 0;
      getnext;
      n := curcs;
      p := curcmd;
      q := curchr;
      getnext;
      if curcmd <> p then
        b := false
      else if curcmd < 111 then
        b := (curchr = q)
      else
        {508:}
begin
        p := mem[curchr].hh.rh;
        q := mem[eqtb[n].hh.rh].hh.rh;
        if p = q then
          b := true
        else
        begin
          while (p <> 0) and (q <> 0) do
            if mem[p].hh.lh <> mem[q].hh.lh then
              p := 0
            else
            begin
              p := mem[p].hh.rh;
              q := mem[q].hh.rh;
            end;
          b := ((p = 0) and (q = 0));
        end;
      end{:508}
;
      scannerstatus := savescannerstatus;
    end{:507}
;
    13:
    begin
      scanfourbitint;
      b := (readopen[curval] = 2);
    end;
    14: b := true;
    15: b := false;
    16:{509:}

    begin
      scanint;
      n := curval;
      if eqtb[5299].int > 1 then
      begin
        begindiagnostic;
        print(782);
        printint(n);
        printchar(125);
        enddiagnostic(false);
      end;
      while n <> 0 do
      begin
        passtext;
        if condptr = savecondptr then
          if curchr = 4 then
            n := n - 1
          else
            goto 50
        else if curchr = 2 then{496:}

        begin
          p := condptr;
          ifline := mem[p + 1].int;
          curif := mem[p].hh.b1;
          iflimit := mem[p].hh.b0;
          condptr := mem[p].hh.rh;
          freenode(p, 2);
        end{:496}
;
      end;
      changeiflimit(4, savecondptr);
      goto 10;
    end{:509}
;
  end{:501}
;
  if eqtb[5299].int > 1 then{502:}

  begin
    begindiagnostic;
    if b then
      print(778)
    else
      print(779);
    enddiagnostic(false);
  end{:502}
;
  if b then
  begin
    changeiflimit(3, savecondptr);
    goto 10;
  end;
  {500:}
while true do
  begin
    passtext;
    if condptr = savecondptr then
    begin
      if curchr <> 4 then
        goto 50;
      begin
        if interaction = 3 then;
        printnl(262);
        print(776);
      end;
      printesc(774);
      begin
        helpptr := 1;
        helpline[0] := 777;
      end;
      error;
    end
    else if curchr = 2 then{496:}

    begin
      p := condptr;
      ifline := mem[p + 1].int;
      curif := mem[p].hh.b1;
      iflimit := mem[p].hh.b0;
      condptr := mem[p].hh.rh;
      freenode(p, 2);
    end{:496}
;
  end{:500}
;
  50:
    if curchr = 2 then{496:}

    begin
      p := condptr;
      ifline := mem[p + 1].int;
      curif := mem[p].hh.b1;
      iflimit := mem[p].hh.b0;
      condptr := mem[p].hh.rh;
      freenode(p, 2);
    end{:496}

    else
      iflimit := 2;
  10: ;
end;
