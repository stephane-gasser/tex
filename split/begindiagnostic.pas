procedure begindiagnostic;
begin
  oldsetting := selector;
  if (eqtb[5292].int <= 0) and (selector = 19) then
  begin
    selector := selector - 1;
    if history = 0 then
      history := 1;
  end;
end;

