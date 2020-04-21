procedure printstyle(c: integer);
begin
  case c div 2 of
    0: printesc(860);
    1: printesc(861);
    2: printesc(862);
    3: printesc(863);
    others: print(864)
  end;
end;
