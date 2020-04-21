procedure fatalerror(s: strnumber);
begin
  normalizeselector;
  begin
    if interaction = 3 then;
    printnl(262);
    print(287);
  end;
  begin
    helpptr := 1;
    helpline[0] := s;
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
