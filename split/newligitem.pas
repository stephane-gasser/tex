function newligitem(c: quarterword): halfword;
var
  p: halfword;
begin
  p := getnode(2);
  mem[p].hh.b1 := c;
  mem[p + 1].hh.rh := 0;
  newligitem := p;
end;
