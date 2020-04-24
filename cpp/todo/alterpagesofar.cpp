#include "alterpagesofar.h"
void alterpagesofar(void)
var
  c: 0..7;
begin
  c := curchr;
  scanoptionalequals;
  scandimen(false, false, false);
  pagesofar[c] := curval;
end;
