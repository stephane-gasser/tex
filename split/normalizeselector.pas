procedure normalizeselector;
begin
  if logopened then
    selector := 19
  else
    selector := 17;
  if jobname = 0 then
    openlogfile;
  if interaction = 0 then
    selector := selector - 1;
end;
