procedure primitive(s: strnumber; c: quarterword; o: halfword);
var
  k: poolpointer;
  j: smallnumber;
  l: smallnumber;
begin
  if s < 256 then
    curval := s + 257
  else
  begin
    k := strstart[s];
    l := strstart[s + 1] - k;
    for j := 0 to l - 1 do
      buffer[j] := strpool[k + j];
    curval := idlookup(0, l);
    begin
      strptr := strptr - 1;
      poolptr := strstart[strptr];
    end;
    hash[curval].rh := s;
  end;
  eqtb[curval].hh.b1 := 1;
  eqtb[curval].hh.b0 := c;
  eqtb[curval].hh.rh := o;
end;
