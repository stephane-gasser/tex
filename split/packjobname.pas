procedure packjobname(s: strnumber);
begin
  curarea := 338;
  curext := s;
  curname := jobname;
  packfilename(curname, curarea, curext);
end;
