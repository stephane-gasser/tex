procedure writedvi(a, b: dviindex);
var
  k: dviindex;
begin
  for k := a to b do
    write(dvifile, dvibuf[k]);
end;
