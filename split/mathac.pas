procedure mathac;
begin
  if curcmd = 45 then{1166:}

  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(1138);
    end;
    printesc(523);
    print(1139);
    begin
      helpptr := 2;
      helpline[1] := 1140;
      helpline[0] := 1141;
    end;
    error;
  end{:1166}
;
  begin
    mem[curlist.tailfield].hh.rh := getnode(5);
    curlist.tailfield := mem[curlist.tailfield].hh.rh;
  end;
  mem[curlist.tailfield].hh.b0 := 28;
  mem[curlist.tailfield].hh.b1 := 0;
  mem[curlist.tailfield + 1].hh := emptyfield;
  mem[curlist.tailfield + 3].hh := emptyfield;
  mem[curlist.tailfield + 2].hh := emptyfield;
  mem[curlist.tailfield + 4].hh.rh := 1;
  scanfifteenbitint;
  mem[curlist.tailfield + 4].hh.b1 := curval mod 256 + 0;
  if (curval >= 28672) and ((eqtb[5307].int >= 0) and (eqtb[5307].int < 16)) then
    mem[
      curlist.tailfield + 4].hh.b0 := eqtb[5307].int
  else
    mem[curlist.tailfield + 4].hh.b0 := (curval div 256) mod 16;
  scanmath(curlist.tailfield + 1);
end;
