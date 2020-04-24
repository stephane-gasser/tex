#include "dvipop.h"
void dvipop(int l)
begin
  if (l = dvioffset + dviptr) and (dviptr > 0) then
    dviptr := dviptr - 1
  else
  begin
    dvibuf[dviptr] := 142;
    dviptr := dviptr + 1;
    if dviptr = dvilimit then
      dviswap;
  end;
end;
