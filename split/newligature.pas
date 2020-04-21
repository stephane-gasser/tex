function newligature(f, c: quarterword; q: halfword): halfword;
var
  p: halfword;
begin
  p := getnode(2);
  mem[p].hh.b0 := 6;
  mem[p + 1].hh.b0 := f;
  mem[p + 1].hh.b1 := c;
  mem[p + 1].hh.rh := q;
  mem[p].hh.b1 := 0;
  newligature := p;
end;
