function newkern(w: scaled): halfword;
var
  p: halfword;
begin
  p := getnode(2);
  mem[p].hh.b0 := 11;
  mem[p].hh.b1 := 0;
  mem[p + 1].int := w;
  newkern := p;
end;
