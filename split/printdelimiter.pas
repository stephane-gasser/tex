procedure printdelimiter(p: halfword);
var
  a: integer;
begin
  a := mem[p].qqqq.b0 * 256 + mem[p].qqqq.b1 - 0;
  a := a * 4096 + mem[p].qqqq.b2 * 256 + mem[p].qqqq.b3 - 0;
  if a < 0 then
    printint(a)
  else
    printhex(a);
end;
