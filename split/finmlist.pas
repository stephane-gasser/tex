function finmlist(p: halfword): halfword;
var
  q: halfword;
begin
  if curlist.auxfield.int <> 0 then{1185:}

  begin
    mem[curlist.auxfield.int + 3].hh.rh := 3;
    mem[curlist.auxfield.int + 3].hh.lh := mem[curlist.headfield].hh.rh;
    if p = 0 then
      q := curlist.auxfield.int
    else
    begin
      q := mem[curlist.auxfield.int + 2].hh.lh;
      if mem[q].hh.b0 <> 30 then
        confusion(876);
      mem[curlist.auxfield.int + 2].hh.lh := mem[q].hh.rh;
      mem[q].hh.rh := curlist.auxfield.int;
      mem[curlist.auxfield.int].hh.rh := p;
    end;
  end{:1185}

  else
  begin
    mem[curlist.tailfield].hh.rh := p;
    q := mem[curlist.headfield].hh.rh;
  end;
  popnest;
  finmlist := q;
end;
