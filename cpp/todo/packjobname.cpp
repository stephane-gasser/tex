#include "packjobname.h"
void packjobname(strnumber s)
begin
  curarea := 338;
  curext := s;
  curname := jobname;
  packfilename(curname, curarea, curext);
end;
