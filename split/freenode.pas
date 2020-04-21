procedure freenode(p: halfword; s: halfword);
var
  q: halfword;
begin
  mem[p].hh.lh := s;
  mem[p].hh.rh := 65535;
  q := mem[rover + 1].hh.lh;
  mem[p + 1].hh.lh := q;
  mem[p + 1].hh.rh := rover;
  mem[rover + 1].hh.lh := p;
  mem[q + 1].hh.rh := p;{varused:=varused-s;}

end;
