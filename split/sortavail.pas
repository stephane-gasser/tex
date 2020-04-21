procedure sortavail;
var
  p, q, r: halfword;
  oldrover: halfword;
begin
  p := getnode(1073741824);
  p := mem[rover + 1].hh.rh;
  mem[rover + 1].hh.rh := 65535;
  oldrover := rover;
  while p <> oldrover do
    {132:}
if p < rover then
    begin
      q := p;
      p := mem[q + 1].hh.rh;
      mem[q + 1].hh.rh := rover;
      rover := q;
    end
    else
    begin
      q := rover;
      while mem[q + 1].hh.rh < p do
        q := mem[q + 1].hh.rh;
      r := mem[p + 1].hh.rh;
      mem[p + 1].hh.rh := mem[q + 1].hh.rh;
      mem[q + 1].hh.rh := p;
      p := r;
    end{:132}
;
  p := rover;
  while mem[p + 1].hh.rh <> 65535 do
  begin
    mem[mem[p + 1].hh.rh + 1].hh.lh := p;
    p := mem[p + 1].hh.rh;
  end;
  mem[p + 1].hh.rh := rover;
  mem[rover + 1].hh.lh := p;
end;
