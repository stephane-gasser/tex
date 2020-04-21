procedure alteraux;
var
  c: halfword;
begin
  if curchr <> abs(curlist.modefield) then
    reportillegalcase
  else
  begin
    c := curchr;
    scanoptionalequals;
    if c = 1 then
    begin
      scandimen(false, false, false);
      curlist.auxfield.int := curval;
    end
    else
    begin
      scanint;
      if (curval <= 0) or (curval > 32767) then
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(1212);
        end;
        begin
          helpptr := 1;
          helpline[0] := 1213;
        end;
        interror(curval);
      end
      else
        curlist.auxfield.hh.lh := curval;
    end;
  end;
end;
