function newdisc: halfword;
var
  p: halfword;
begin
  p := getnode(2);
  mem[p].hh.b0 := 7;
  mem[p].hh.b1 := 0;
  mem[p + 1].hh.lh := 0;
  mem[p + 1].hh.rh := 0;
  newdisc := p;
end;
