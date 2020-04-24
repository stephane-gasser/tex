#include "makenamestring.h"
strnumber makenamestring(void)
var
  k: 1..filenamesize;
begin
  if (poolptr + namelength > poolsize) or (strptr = maxstrings) or ((poolptr - strstart[strptr]) > 0) then
    makenamestring := 63
  else
  begin
    for k := 1 to
      namelength do
    begin
      strpool[poolptr] := xord[nameoffile[k]];
      poolptr := poolptr + 1;
    end;
    makenamestring := makestring;
  end;
end;
