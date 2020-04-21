procedure confusion(s: strnumber);
begin
  normalizeselector;
  if history < 2 then
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(291);
    end;
    print(s);
    printchar(41);
    begin
      helpptr := 1;
      helpline[0] := 292;
    end;
  end
  else
  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(293);
    end;
    begin
      helpptr := 2;
      helpline[1] := 294;
      helpline[0] := 295;
    end;
  end;
  begin
    if interaction = 3 then
      interaction := 2;
    if logopened then
      error;
    {if interaction>0 then debughelp;}
history := 3;
    jumpout;
  end;
end;
