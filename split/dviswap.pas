procedure dviswap;
begin
  if dvilimit = dvibufsize then
  begin
    writedvi(0, halfbuf - 1);
    dvilimit := halfbuf;
    dvioffset := dvioffset + dvibufsize;
    dviptr := 0;
  end
  else
  begin
    writedvi(halfbuf, dvibufsize - 1);
    dvilimit := dvibufsize;
  end;
  dvigone := dvigone + halfbuf;
end;
