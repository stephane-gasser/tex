function makeleftright(q: halfword; style: smallnumber; maxd, maxh: scaled): smallnumber;
var
  delta, delta1, delta2: scaled;
begin
  if style < 4 then
    cursize := 0
  else
    cursize := 16 * ((style - 2) div 2);
  delta2 := maxd + fontinfo[22 + parambase[eqtb[3937 + cursize].hh.rh]].int;
  delta1 := maxh + maxd - delta2;
  if delta2 > delta1 then
    delta1 := delta2;
  delta := (delta1 div 500) * eqtb[5281].int;
  delta2 := delta1 + delta1 - eqtb[5840].int;
  if delta < delta2 then
    delta := delta2;
  mem[q + 1].int := vardelimiter(q + 1, cursize, delta);
  makeleftright := mem[q].hh.b0 - (10);
end;
