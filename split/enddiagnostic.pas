procedure enddiagnostic(blankline: boolean);
begin
  printnl(338);
  if blankline then
    println;
  selector := oldsetting;
end;

