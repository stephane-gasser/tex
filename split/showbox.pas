procedure showbox(p: halfword);
begin
  {236:}
depththreshold := eqtb[5288].int;
  breadthmax := eqtb[5287].int{:236}
;
  if breadthmax <= 0 then
    breadthmax := 5;
  if poolptr + depththreshold >= poolsize then
    depththreshold := poolsize - poolptr - 1;
  shownodelist(p);
  println;
end;
