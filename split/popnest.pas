procedure popnest;
begin
  begin
    mem[curlist.headfield].hh.rh := avail;
    avail := curlist.headfield;{dynused:=dynused-1;}

  end;
  nestptr := nestptr - 1;
  curlist := nest[nestptr];
end;
