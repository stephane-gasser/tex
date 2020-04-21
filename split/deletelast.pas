procedure deletelast;
label
  10;
var
  p, q: halfword;
  m: quarterword;
begin
  if (curlist.modefield = 1) and (curlist.tailfield = curlist.headfield) then{1106:}

  begin
    if (curchr <> 10) or (lastglue <> 65535) then
    begin
      youcant;
      begin
        helpptr := 2;
        helpline[1] := 1070;
        helpline[0] := 1086;
      end;
      if curchr = 11 then
        helpline[0] := (1087)
      else if curchr <> 10 then
        helpline[0] := (1088);
      error;
    end;
  end{:1106}

  else if not (curlist.tailfield >= himemmin) then
    if mem[curlist.tailfield].hh.b0 = curchr then
    begin
      q := curlist.headfield;
      repeat
        p := q;
        if not (q >= himemmin) then
          if mem[q].hh.b0 = 7 then
          begin
            for m := 1 to mem[q].hh.b1 do
              p := mem[p].hh.rh;
            if p = curlist.tailfield then
              goto 10;
          end;
        q := mem[p].hh.rh;
      until q = curlist.tailfield;
      mem[p].hh.rh := 0;
      flushnodelist(curlist.tailfield);
      curlist.tailfield := p;
    end;
  10: ;
end;
