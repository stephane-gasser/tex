procedure doregistercommand(a: smallnumber);
label
  40, 10;
var
  l, q, r, s: halfword;
  p: 0..3;
begin
  q := curcmd;
  {1237:}
begin
    if q <> 89 then
    begin
      getxtoken;
      if (curcmd >= 73) and (curcmd <= 76) then
      begin
        l := curchr;
        p := curcmd - 73;
        goto 40;
      end;
      if curcmd <> 89 then
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(685);
        end;
        printcmdchr(curcmd, curchr);
        print(686);
        printcmdchr(q, 0);
        begin
          helpptr := 1;
          helpline[0] := 1209;
        end;
        error;
        goto 10;
      end;
    end;
    p := curchr;
    scaneightbitint;
    case p of
      0: l := curval + 5318;
      1: l := curval + 5851;
      2: l := curval + 2900;
      3: l := curval + 3156;
    end;
  end;
  40:
  {:1237}
;
  if q = 89 then
    scanoptionalequals
  else if scankeyword(1205) then;
  aritherror := false;
  if q < 91 then
    {1238:}
if p < 2 then
    begin
      if p = 0 then
        scanint
      else
        scandimen(
          false, false, false);
      if q = 90 then
        curval := curval + eqtb[l].int;
    end
    else
    begin
      scanglue(p);
      if q = 90 then{1239:}

      begin
        q := newspec(curval);
        r := eqtb[l].hh.rh;
        deleteglueref(curval);
        mem[q + 1].int := mem[q + 1].int + mem[r + 1].int;
        if mem[q + 2].int = 0 then
          mem[q].hh.b0 := 0;
        if mem[q].hh.b0 = mem[r].hh.b0 then
          mem[q + 2].int := mem[q + 2].int + mem[r + 2].int
        else if (mem[q].hh.b0 < mem[r].hh.b0) and (mem[r + 2].int <> 0) then
        begin
          mem
            [q + 2].int := mem[r + 2].int;
          mem[q].hh.b0 := mem[r].hh.b0;
        end;
        if mem[q + 3].int = 0 then
          mem[q].hh.b1 := 0;
        if mem[q].hh.b1 = mem[r].hh.b1 then
          mem[q + 3].int := mem[q + 3].int + mem[r + 3].int
        else if (mem[q].hh.b1 < mem[r].hh.b1) and (mem[r + 3].int <> 0) then
        begin
          mem
            [q + 3].int := mem[r + 3].int;
          mem[q].hh.b1 := mem[r].hh.b1;
        end;
        curval := q;
      end{:1239}
;
    end{:1238}

  else{1240:}

  begin
    scanint;
    if p < 2 then
      if q = 91 then
        if p = 0 then
          curval := multandadd(eqtb[l].int, curval, 0, 2147483647)
        else
          curval := multandadd(eqtb[l].int, curval, 0, 1073741823)
      else
        curval := xovern(eqtb[l].int, curval)
    else
    begin
      s := eqtb[l].hh.rh;
      r := newspec(s);
      if q = 91 then
      begin
        mem[r + 1].int := multandadd(mem[s + 1].int, curval, 0, 1073741823);
        mem[r + 2].int := multandadd(mem[s + 2].int, curval, 0, 1073741823);
        mem[r + 3].int := multandadd(mem[s + 3].int, curval, 0, 1073741823);
      end
      else
      begin
        mem[r + 1].int := xovern(mem[s + 1].int, curval);
        mem[r + 2].int := xovern(mem[s + 2].int, curval);
        mem[r + 3].int := xovern(mem[s + 3].int, curval);
      end;
      curval := r;
    end;
  end{:1240}
;
  if aritherror then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(1206);
    end;
    begin
      helpptr := 2;
      helpline[1] := 1207;
      helpline[0] := 1208;
    end;
    if p >= 2 then
      deleteglueref(curval);
    error;
    goto 10;
  end;
  if p < 2 then
    if (a >= 4) then
      geqworddefine(l, curval)
    else
      eqworddefine(l,
        curval)
  else
  begin
    trapzeroglue;
    if (a >= 4) then
      geqdefine(l, 117, curval)
    else
      eqdefine(l, 117, curval);
  end;
  10: ;
end;
