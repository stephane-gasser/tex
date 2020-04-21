function privileged: boolean;
begin
  if curlist.modefield > 0 then
    privileged := true
  else
  begin
    reportillegalcase;
    privileged := false;
  end;
end;
