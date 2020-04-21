procedure flushlist(p: halfword);
var
  q, r: halfword;
begin
  if p <> 0 then
  begin
    r := p;
    repeat
      q := r;
      r := mem[r].hh.rh;
      {dynused:=dynused-1;}
until r = 0;
    mem[q].hh.rh := avail;
    avail := p;
  end;
end;
