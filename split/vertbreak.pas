function vertbreak(p: halfword; h, d: scaled): halfword;
label
  30, 45, 90;
var
  prevp: halfword;
  q, r: halfword;
  pi: integer;
  b: integer;
  leastcost: integer;
  bestplace: halfword;
  prevdp: scaled;
  t: smallnumber;
begin
  prevp := p;
  leastcost := 1073741823;
  activewidth[1] := 0;
  activewidth[2] := 0;
  activewidth[3] := 0;
  activewidth[4] := 0;
  activewidth[5] := 0;
  activewidth[6] := 0;
  prevdp := 0;
  while true do
  begin
    {972:}
if p = 0 then
      pi := -10000
    else
      {973:}
case mem[p].hh.b0 of
        0, 1, 2:
        begin
          activewidth[1] := activewidth[1] + prevdp + mem[p + 3].int;
          prevdp := mem[p + 2].int;
          goto 45;
        end;
        8:{1365:}
goto 45{:1365}
;
        10: if (mem[prevp].hh.b0 < 9) then
            pi := 0
          else
            goto 90;
        11:
        begin
          if mem[p].hh.rh = 0 then
            t := 12
          else
            t := mem[mem[p].hh.rh].hh.b0;
          if t = 10 then
            pi := 0
          else
            goto 90;
        end;
        12: pi := mem[p + 1].int;
        4, 3: goto 45;
        others: confusion(959)
      end{:973}
;
    {974:}
if pi < 10000 then
    begin
      {975:}
if activewidth[1] < h then
        if (activewidth[3] <> 0) or (activewidth[4] <> 0) or (activewidth[5] <> 0) then
          b := 0
        else
          b := badness(h - activewidth[1], activewidth[2])
      else if activewidth[1] - h > activewidth[6] then
        b := 1073741823
      else
        b := badness(activewidth[1] - h, activewidth[6]){:975}
;
      if b < 1073741823 then
        if pi <= -10000 then
          b := pi
        else if b < 10000 then
          b := b + pi
        else
          b := 100000;
      if b <= leastcost then
      begin
        bestplace := p;
        leastcost := b;
        bestheightplusdepth := activewidth[1] + prevdp;
      end;
      if (b = 1073741823) or (pi <= -10000) then
        goto 30;
    end{:974}
;
    if (mem[p].hh.b0 < 10) or (mem[p].hh.b0 > 11) then
      goto 45;
    90:
      {976:}
if mem[p].hh.b0 = 11 then
        q := p
      else
      begin
        q := mem[p + 1].hh.lh;
        activewidth[2 + mem[q].hh.b0] := activewidth[2 + mem[q].hh.b0] + mem[q + 2].int;
        activewidth[6] := activewidth[6] + mem[q + 3].int;
        if (mem[q].hh.b1 <> 0) and (mem[q + 3].int <> 0) then
        begin
          begin
            if interaction = 3 then;
            printnl(262);
            print(960);
          end;
          begin
            helpptr := 4;
            helpline[3] := 961;
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
    activewidth[1] := activewidth[1] + prevdp + mem[q + 1].int;
    prevdp := 0{:976}
;
    45:
      if prevdp > d then
      begin
        activewidth[1] := activewidth[1] + prevdp - d;
        prevdp := d;
      end;
    {:972}
;
    prevp := p;
    p := mem[prevp].hh.rh;
  end;
  30:
    vertbreak := bestplace;
end;
