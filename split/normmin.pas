function normmin(h: integer): smallnumber;
begin
  if h <= 0 then
    normmin := 1
  else if h >= 63 then
    normmin := 63
  else
    normmin := h;
end;
