procedure mathfraction;
var
  c: smallnumber;
begin
  c := curchr;
  if curlist.auxfield.int <> 0 then{1183:}

  begin
    if c >= 3 then
    begin
      scandelimiter(29988, false);
      scandelimiter(29988, false);
    end;
    if c mod 3 = 0 then
      scandimen(false, false, false);
    begin
      if interaction = 3 then;
      printnl(262);
      print(1152);
    end;
    begin
      helpptr := 3;
      helpline[2] := 1153;
      helpline[1] := 1154;
      helpline[0] := 1155;
    end;
    error;
  end{:1183}

  else
  begin
    curlist.auxfield.int := getnode(6);
    mem[curlist.auxfield.int].hh.b0 := 25;
    mem[curlist.auxfield.int].hh.b1 := 0;
    mem[curlist.auxfield.int + 2].hh.rh := 3;
    mem[curlist.auxfield.int + 2].hh.lh := mem[curlist.headfield].hh.rh;
    mem[curlist.auxfield.int + 3].hh := emptyfield;
    mem[curlist.auxfield.int + 4].qqqq := nulldelimiter;
    mem[curlist.auxfield.int + 5].qqqq := nulldelimiter;
    mem[curlist.headfield].hh.rh := 0;
    curlist.tailfield := curlist.headfield;
    {1182:}
if c >= 3 then
    begin
      scandelimiter(curlist.auxfield.int + 4, false);
      scandelimiter(curlist.auxfield.int + 5, false);
    end;
    case c mod 3 of
      0:
      begin
        scandimen(false, false, false);
        mem[curlist.auxfield.int + 1].int := curval;
      end;
      1: mem[curlist.auxfield.int + 1].int := 1073741824;
      2: mem[curlist.auxfield.int + 1].int := 0;
    end{:1182}
;
  end;
end;
