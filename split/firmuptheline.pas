procedure firmuptheline;
var
  k: 0..bufsize;
begin
  curinput.limitfield := last;
  if eqtb[5291].int > 0 then
    if interaction > 1 then
    begin
      ;
      println;
      if curinput.startfield < curinput.limitfield then
        for k := curinput.startfield to curinput.limitfield - 1 do
          print(buffer[k]);
      First := curinput.limitfield;
      begin
        ;
        print(618);
        terminput;
      end;
      if last > First then
      begin
        for k := First to last - 1 do
          buffer[k + curinput.startfield - First] := buffer[k];
        curinput.limitfield := curinput.startfield + last - First;
      end;
    end;
end;
