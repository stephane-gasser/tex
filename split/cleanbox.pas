function cleanbox(p: halfword; s: smallnumber): halfword;
label
  40;
var
  q: halfword;
  savestyle: smallnumber;
  x: halfword;
  r: halfword;
begin
  case mem[p].hh.rh of
    1:
    begin
      curmlist := newnoad;
      mem[curmlist + 1] := mem[p];
    end;
    2:
    begin
      q := mem[p].hh.lh;
      goto 40;
    end;
    3: curmlist := mem[p].hh.lh;
    others:
    begin
      q := newnullbox;
      goto 40;
    end
  end;
  savestyle := curstyle;
  curstyle := s;
  mlistpenalties := false;
  mlisttohlist;
  q := mem[29997].hh.rh;
  curstyle := savestyle;
  {703:}
begin
    if curstyle < 4 then
      cursize := 0
    else
      cursize := 16 * ((curstyle - 2) div 2);
    curmu := xovern(fontinfo[6 + parambase[eqtb[3937 + cursize].hh.rh]].int, 18);
  end{:703}
;
  40:
    if (q >= himemmin) or (q = 0) then
      x := hpack(q, 0, 1)
    else if (mem[q].hh.rh = 0) and (mem[q].hh.b0 <= 1) and (mem[q + 4].int = 0) then
      x := q
    else
      x := hpack(q, 0, 1);
  {721:}
q := mem[x + 5].hh.rh;
  if (q >= himemmin) then
  begin
    r := mem[q].hh.rh;
    if r <> 0 then
      if mem[r].hh.rh = 0 then
        if not (r >= himemmin) then
          if mem[r].hh.b0 = 11 then
          begin
            freenode(r, 2);
            mem[q].hh.rh := 0;
          end;
  end{:721}
;
  cleanbox := x;
end;
