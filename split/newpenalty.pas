function newpenalty(m: integer): halfword;
var
  p: halfword;
begin
  p := getnode(2);
  mem[p].hh.b0 := 12;
  mem[p].hh.b1 := 0;
  mem[p + 1].int := m;
  newpenalty := p;
end;

