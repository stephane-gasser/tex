function getavail: halfword;
var
  p: halfword;
begin
  p := avail;
  if p <> 0 then
    avail := mem[avail].hh.rh
  else if memend < memmax then
  begin
    memend := memend + 1;
    p := memend;
  end
  else
  begin
    himemmin := himemmin - 1;
    p := himemmin;
    if himemmin <= lomemmax then
    begin
      runaway;
      overflow(300, memmax + 1 - memmin);
    end;
  end;
  mem[p].hh.rh := 0;
  {dynused:=dynused+1;}
getavail := p;
end;
