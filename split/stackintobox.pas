procedure stackintobox(b: halfword; f: internalfontnumber; c: quarterword);
var
  p: halfword;
begin
  p := charbox(f, c);
  mem[p].hh.rh := mem[b + 5].hh.rh;
  mem[b + 5].hh.rh := p;
  mem[b + 3].int := mem[p + 3].int;
end;
