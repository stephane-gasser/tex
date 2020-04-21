procedure packfilename(n, a, e: strnumber);
var
  k: integer;
  c: ASCIIcode;
  j: poolpointer;
begin
  k := 0;
  for j := strstart[a] to strstart[a + 1] - 1 do
  begin
    c := strpool[j];
    k := k + 1;
    if k <= filenamesize then
      nameoffile[k] := xchr[c];
  end;
  for j := strstart[n] to strstart[n + 1] - 1 do
  begin
    c := strpool[j];
    k := k + 1;
    if k <= filenamesize then
      nameoffile[k] := xchr[c];
  end;
  for j := strstart[e] to strstart[e + 1] - 1 do
  begin
    c := strpool[j];
    k := k + 1;
    if k <= filenamesize then
      nameoffile[k] := xchr[c];
  end;
  if k <= filenamesize then
    namelength := k
  else
    namelength := filenamesize;
  for k := namelength + 1 to filenamesize do
    nameoffile[k] := ' ';
end;
