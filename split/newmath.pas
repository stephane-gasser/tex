function newmath(w: scaled; s: smallnumber): halfword;
var
  p: halfword;
begin
  p := getnode(2);
  mem[p].hh.b0 := 9;
  mem[p].hh.b1 := s;
  mem[p + 1].int := w;
  newmath := p;
end;

