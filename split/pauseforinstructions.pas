procedure pauseforinstructions;
begin
  if OKtointerrupt then
  begin
    interaction := 3;
    if (selector = 18) or (selector = 16) then
      selector := selector + 1;
    begin
      if interaction = 3 then;
      printnl(262);
      print(296);
    end;
    begin
      helpptr := 3;
      helpline[2] := 297;
      helpline[1] := 298;
      helpline[0] := 299;
    end;
    deletionsallowed := false;
    error;
    deletionsallowed := true;
    interrupt := 0;
  end;
end;
