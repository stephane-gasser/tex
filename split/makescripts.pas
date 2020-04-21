procedure makescripts(q: halfword; delta: scaled);
var
  p, x, y, z: halfword;
  shiftup, shiftdown, clr: scaled;
  t: smallnumber;
begin
  p := mem[q + 1].int;
  if (p >= himemmin) then
  begin
    shiftup := 0;
    shiftdown := 0;
  end
  else
  begin
    z := hpack(p, 0, 1);
    if curstyle < 4 then
      t := 16
    else
      t := 32;
    shiftup := mem[z + 3].int - fontinfo[18 + parambase[eqtb[3937 + t].hh.rh]].int;
    shiftdown := mem[z + 2].int + fontinfo[19 + parambase[eqtb[3937 + t].hh.rh]].int;
    freenode(z, 7);
  end;
  if mem[q + 2].hh.rh = 0 then{757:}

  begin
    x := cleanbox(q + 3, 2 * (curstyle div 4) + 5);
    mem[x + 1].int := mem[x + 1].int + eqtb[5842].int;
    if shiftdown < fontinfo[16 + parambase[eqtb[3937 + cursize].hh.rh]].int then
      shiftdown := fontinfo[16 + parambase[eqtb[3937 + cursize].hh.rh]].int;
    clr := mem[x + 3].int - (abs(fontinfo[5 + parambase[eqtb[3937 + cursize].hh.rh]].int * 4) div 5);
    if shiftdown < clr then
      shiftdown := clr;
    mem[x + 4].int := shiftdown;
  end{:757}

  else
  begin{758:}

    begin
      x := cleanbox(q + 2, 2 * (curstyle div 4) + 4 + (curstyle mod 2));
      mem[x + 1].int := mem[x + 1].int + eqtb[5842].int;
      if odd(curstyle) then
        clr := fontinfo[15 + parambase[eqtb[3937 + cursize].hh.rh]].int
      else if curstyle < 2 then
        clr := fontinfo[13 + parambase[eqtb[3937 + cursize].hh.rh]].int
      else
        clr := fontinfo[14 + parambase[eqtb[3937 + cursize].hh.rh]].int;
      if shiftup < clr then
        shiftup := clr;
      clr := mem[x + 2].int + (abs(fontinfo[5 + parambase[eqtb[3937 + cursize].hh.rh]].int) div 4);
      if shiftup < clr then
        shiftup := clr;
    end{:758}
;
    if mem[q + 3].hh.rh = 0 then
      mem[x + 4].int := -shiftup
    else{759:}

    begin
      y :=
        cleanbox(q + 3, 2 * (curstyle div 4) + 5);
      mem[y + 1].int := mem[y + 1].int + eqtb[5842].int;
      if shiftdown < fontinfo[17 + parambase[eqtb[3937 + cursize].hh.rh]].int then
        shiftdown := fontinfo[17 + parambase[eqtb[3937 + cursize].hh.rh]].int;
      clr := 4 * fontinfo[8 + parambase[eqtb[3938 + cursize].hh.rh]].int - ((shiftup - mem[x + 2].int) - (mem[y + 3].int - shiftdown));
      if clr > 0 then
      begin
        shiftdown := shiftdown + clr;
        clr := (abs(fontinfo[5 + parambase[eqtb[3937 + cursize].hh.rh]].int * 4) div 5) - (shiftup - mem[x + 2].int);
        if clr > 0 then
        begin
          shiftup := shiftup + clr;
          shiftdown := shiftdown - clr;
        end;
      end;
      mem[x + 4].int := delta;
      p := newkern((shiftup - mem[x + 2].int) - (mem[y + 3].int - shiftdown));
      mem[x].hh.rh := p;
      mem[p].hh.rh := y;
      x := vpackage(x, 0, 1, 1073741823);
      mem[x + 4].int := shiftdown;
    end{:759}
;
  end;
  if mem[q + 1].int = 0 then
    mem[q + 1].int := x
  else
  begin
    p := mem[q + 1].int;
    while mem[p].hh.rh <> 0 do
      p := mem[p].hh.rh;
    mem[p].hh.rh := x;
  end;
end;
