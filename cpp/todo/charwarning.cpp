#include "charwarning.h"
void charwarning(internalfontnumber f, eightbits c)
begin
  if eqtb[5298].int > 0 then
  begin
    begindiagnostic;
    printnl(824);
    print(c);
    print(825);
    slowprint(fontname[f]);
    printchar(33);
    enddiagnostic(false);
  end;
end;
