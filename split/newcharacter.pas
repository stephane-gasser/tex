function newcharacter(f: internalfontnumber; c: eightbits): halfword;
label
  10;
var
  p: halfword;
begin
  if fontbc[f] <= c then
    if fontec[f] >= c then
      if (fontinfo[charbase[f] + c + 0].qqqq.b0 > 0) then
      begin
        p := getavail;
        mem[p].hh.b0 := f;
        mem[p].hh.b1 := c + 0;
        newcharacter := p;
        goto 10;
      end;
  charwarning(f, c);
  newcharacter := 0;
  10: ;
end;
