procedure printmode(m: integer);
begin
  if m > 0 then
    case m div (101) of
      0: print(355);
      1: print(356);
      2: print(357);
    end
  else if m = 0 then
    print(358)
  else
    case (-m) div (101) of
      0: print(359);
      1: print(360);
      2: print(343);
    end;
  print(361);
end;
