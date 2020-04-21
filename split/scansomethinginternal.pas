procedure scansomethinginternal(level: smallnumber; negative: boolean);
var
  m: halfword;
  p: 0..nestsize;
begin
  m := curchr;
  case curcmd of
    85:{414:}

    begin
      scancharnum;
      if m = 5007 then
      begin
        curval := eqtb[5007 + curval].hh.rh - 0;
        curvallevel := 0;
      end
      else if m < 5007 then
      begin
        curval := eqtb[m + curval].hh.rh;
        curvallevel := 0;
      end
      else
      begin
        curval := eqtb[m + curval].int;
        curvallevel := 0;
      end;
    end{:414}
;
    71, 72, 86, 87, 88:{415:}
if level <> 5 then
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(664);
        end;
        begin
          helpptr := 3;
          helpline[2] := 665;
          helpline[1] := 666;
          helpline[0] := 667;
        end;
        backerror;
        begin
          curval := 0;
          curvallevel := 1;
        end;
      end
      else if curcmd <= 72 then
      begin
        if curcmd < 72 then
        begin
          scaneightbitint;
          m := 3422 + curval;
        end;
        begin
          curval := eqtb[m].hh.rh;
          curvallevel := 5;
        end;
      end
      else
      begin
        backinput;
        scanfontident;
        begin
          curval := 2624 + curval;
          curvallevel := 4;
        end;
      end{:415}
;
    73:
    begin
      curval := eqtb[m].int;
      curvallevel := 0;
    end;
    74:
    begin
      curval := eqtb[m].int;
      curvallevel := 1;
    end;
    75:
    begin
      curval := eqtb[m].hh.rh;
      curvallevel := 2;
    end;
    76:
    begin
      curval := eqtb[m].hh.rh;
      curvallevel := 3;
    end;
    79:{418:}
if abs(curlist.modefield) <> m then
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(680);
        end;
        printcmdchr(79, m);
        begin
          helpptr := 4;
          helpline[3] := 681;
          helpline[2] := 682;
          helpline[1] := 683;
          helpline[0] := 684;
        end;
        error;
        if level <> 5 then
        begin
          curval := 0;
          curvallevel := 1;
        end
        else
        begin
          curval := 0;
          curvallevel := 0;
        end;
      end
      else if m = 1 then
      begin
        curval := curlist.auxfield.int;
        curvallevel := 1;
      end
      else
      begin
        curval := curlist.auxfield.hh.lh;
        curvallevel := 0;
      end{:418}
;
    80:{422:}
if curlist.modefield = 0 then
      begin
        curval := 0;
        curvallevel := 0;
      end
      else
      begin
        nest[nestptr] := curlist;
        p := nestptr;
        while abs(nest[p].modefield) <> 1 do
          p := p - 1;
        begin
          curval := nest[p].pgfield;
          curvallevel := 0;
        end;
      end{:422}
;
    82:{419:}

    begin
      if m = 0 then
        curval := deadcycles
      else
        curval :=
          insertpenalties;
      curvallevel := 0;
    end{:419}
;
    81:{421:}

    begin
      if (pagecontents = 0) and (not outputactive) then
        if m = 0 then
          curval := 1073741823
        else
          curval := 0
      else
        curval := pagesofar[m];
      curvallevel := 1;
    end{:421}
;
    84:{423:}

    begin
      if eqtb[3412].hh.rh = 0 then
        curval := 0
      else
        curval := mem[eqtb[3412].hh.rh].hh.lh;
      curvallevel := 0;
    end{:423}
;
    83:{420:}

    begin
      scaneightbitint;
      if eqtb[3678 + curval].hh.rh = 0 then
        curval := 0
      else
        curval := mem[eqtb[3678 + curval].hh.rh + m].int;
      curvallevel := 1;
    end{:420}
;
    68, 69:
    begin
      curval := curchr;
      curvallevel := 0;
    end;
    77:{425:}

    begin
      findfontdimen(false);
      fontinfo[fmemptr].int := 0;
      begin
        curval := fontinfo[curval].int;
        curvallevel := 1;
      end;
    end{:425}
;
    78:{426:}

    begin
      scanfontident;
      if m = 0 then
      begin
        curval := hyphenchar[curval];
        curvallevel := 0;
      end
      else
      begin
        curval := skewchar[curval];
        curvallevel := 0;
      end;
    end{:426}
;
    89:{427:}

    begin
      scaneightbitint;
      case m of
        0: curval := eqtb[5318 + curval].int;
        1: curval := eqtb[5851 + curval].int;
        2: curval := eqtb[2900 + curval].hh.rh;
        3: curval := eqtb[3156 + curval].hh.rh;
      end;
      curvallevel := m;
    end{:427}
;
    70:{424:}
if curchr > 2 then
      begin
        if curchr = 3 then
          curval := line
        else
          curval := lastbadness;
        curvallevel := 0;
      end
      else
      begin
        if curchr = 2 then
          curval := 0
        else
          curval := 0;
        curvallevel := curchr;
        if not (curlist.tailfield >= himemmin) and (curlist.modefield <> 0) then
          case
            curchr of
            0: if mem[curlist.tailfield].hh.b0 = 12 then
                curval := mem[curlist.tailfield + 1].int;
            1: if mem[curlist.tailfield].hh.b0 = 11 then
                curval := mem[curlist.tailfield + 1].int;
            2: if mem[curlist.tailfield].hh.b0 = 10 then
              begin
                curval := mem[curlist.tailfield + 1].hh.lh;
                if mem[curlist.tailfield].hh.b1 = 99 then
                  curvallevel := 3;
              end;
          end
        else if (curlist.modefield = 1) and (curlist.tailfield = curlist.headfield) then
          case curchr of
            0: curval := lastpenalty;
            1: curval := lastkern;
            2: if lastglue <> 65535 then
                curval := lastglue;
          end;
      end{:424}
;
    others:{428:}

    begin
      begin
        if interaction = 3 then;
        printnl(262);
        print(685);
      end;
      printcmdchr(curcmd, curchr);
      print(686);
      printesc(537);
      begin
        helpptr := 1;
        helpline[0] := 684;
      end;
      error;
      if level <> 5 then
      begin
        curval := 0;
        curvallevel := 1;
      end
      else
      begin
        curval := 0;
        curvallevel := 0;
      end;
    end{:428}

  end;
  while curvallevel > level do{429:}

  begin
    if curvallevel = 2 then
      curval := mem[curval + 1].int
    else if curvallevel = 3 then
      muerror;
    curvallevel := curvallevel - 1;
  end{:429}
;
  {430:}
if negative then
    if curvallevel >= 2 then
    begin
      curval := newspec(curval);{431:}

      begin
        mem[curval + 1].int := -mem[curval + 1].int;
        mem[curval + 2].int := -mem[curval + 2].int;
        mem[curval + 3].int := -mem[curval + 3].int;
      end{:431}
;
    end
    else
      curval := -curval
  else if (curvallevel >= 2) and (curvallevel <= 3) then
    mem[curval].hh.rh := mem[curval].hh.rh + 1{:430}
;
end;
