procedure subsup;
var
  t: smallnumber;
  p: halfword;
begin
  t := 0;
  p := 0;
  if curlist.tailfield <> curlist.headfield then
    if (mem[curlist.tailfield].hh.b0 >= 16) and (mem[curlist.tailfield].hh.b0 < 30) then
    begin
      p := curlist.tailfield + 2 + curcmd - 7;
      t := mem[p].hh.rh;
    end;
  if (p = 0) or (t <> 0) then{1177:}

  begin
    begin
      mem[curlist.tailfield].hh.rh :=
        newnoad;
      curlist.tailfield := mem[curlist.tailfield].hh.rh;
    end;
    p := curlist.tailfield + 2 + curcmd - 7;
    if t <> 0 then
    begin
      if curcmd = 7 then
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(1142);
        end;
        begin
          helpptr := 1;
          helpline[0] := 1143;
        end;
      end
      else
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(1144);
        end;
        begin
          helpptr := 1;
          helpline[0] := 1145;
        end;
      end;
      error;
    end;
  end{:1177}
;
  scanmath(p);
end;
