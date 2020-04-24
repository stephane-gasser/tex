#include "boxerror.h"
void boxerror(eightbits n)
begin
  error;
  begindiagnostic;
  printnl(835);
  showbox(eqtb[3678 + n].hh.rh);
  enddiagnostic(true);
  flushnodelist(eqtb[3678 + n].hh.rh);
  eqtb[3678 + n].hh.rh := 0;
end;
