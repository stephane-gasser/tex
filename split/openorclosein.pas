procedure openorclosein;
var
  c: 0..1;
  n: 0..15;
begin
  c := curchr;
  scanfourbitint;
  n := curval;
  if readopen[n] <> 2 then
  begin
    aclose(readfile[n]);
    readopen[n] := 2;
  end;
  if c <> 0 then
  begin
    scanoptionalequals;
    scanfilename;
    if curext = 338 then
      curext := 790;
    packfilename(curname, curarea, curext);
    if aopenin(readfile[n]) then
      readopen[n] := 1;
  end;
end;
