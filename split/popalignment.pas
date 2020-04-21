procedure popalignment;
var
  p: halfword;
begin
  begin
    mem[curhead].hh.rh := avail;
    avail := curhead;
    {dynused:=dynused-1;}
end;
  p := alignptr;
  curtail := mem[p + 4].hh.rh;
  curhead := mem[p + 4].hh.lh;
  alignstate := mem[p + 3].int;
  curloop := mem[p + 2].int;
  curspan := mem[p + 1].hh.rh;
  mem[29992].hh.rh := mem[p + 1].hh.lh;
  curalign := mem[p].hh.lh;
  alignptr := mem[p].hh.rh;
  freenode(p, 5);
end;
