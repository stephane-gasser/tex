procedure terminput;
var
  k: 0..bufsize;
begin
  break(termout);
  if not inputln(termin, true) then
    fatalerror(261);
  termoffset := 0;
  selector := selector - 1;
  if last <> First then
    for k := First to last - 1 do
      print(buffer[k]);
  println;
  selector := selector + 1;
end;
