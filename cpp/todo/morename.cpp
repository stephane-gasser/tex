#include "morename.h"
bool morename(ASCIIcode c)
begin
  if c = 32 then
    morename := false
  else
  begin
    begin
      if poolptr + 1 > poolsize then
        overflow(257, poolsize - initpoolptr);
    end;
    begin
      strpool[poolptr] := c;
      poolptr := poolptr + 1;
    end;
    if (c = 62) or (c = 58) then
    begin
      areadelimiter := (poolptr - strstart[strptr]);
      extdelimiter := 0;
    end
    else if (c = 46) and (extdelimiter = 0) then
      extdelimiter := (poolptr - strstart[strptr]);
    morename := true;
  end;
end;
