procedure printthedigs(k: eightbits);
begin
  while k > 0 do
  begin
    k := k - 1;
    if dig[k] < 10 then
      printchar(48 + dig[k])
    else
      printchar(55 + dig[k]);
  end;
end;
