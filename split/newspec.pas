function newspec(p: halfword): halfword;
var
  q: halfword;
begin
  q := getnode(4);
  mem[q] := mem[p];
  mem[q].hh.rh := 0;
  mem[q + 1].int := mem[p + 1].int;
  mem[q + 2].int := mem[p + 2].int;
  mem[q + 3].int := mem[p + 3].int;
  newspec := q;
end;
