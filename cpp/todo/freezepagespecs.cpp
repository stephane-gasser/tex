#include "freezepagespecs.h"
void freezepagespecs(smallnumber s)
begin
  pagecontents := s;
  pagesofar[0] := eqtb[5834].int;
  pagemaxdepth := eqtb[5835].int;
  pagesofar[7] := 0;
  pagesofar[1] := 0;
  pagesofar[2] := 0;
  pagesofar[3] := 0;
  pagesofar[4] := 0;
  pagesofar[5] := 0;
  pagesofar[6] := 0;
  leastpagecost := 1073741823;
{if eqtb[5296].int>0 then begin begindiagnostic;printnl(986);
printscaled(pagesofar[0]);print(987);printscaled(pagemaxdepth);
enddiagnostic(false);end;}
end;
