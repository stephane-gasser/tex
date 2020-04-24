#include "alterinteger.h"
void alterinteger(void)
var
  c: 0..1;
begin
  c := curchr;
  scanoptionalequals;
  scanint;
  if c = 0 then
    deadcycles := curval
  else
    insertpenalties := curval;
end;
