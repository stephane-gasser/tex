#include "writedvi.h"
void writedvi(dviindex a, dviindex  b)
var
  k: dviindex;
begin
  for k := a to b do
    write(dvifile, dvibuf[k]);
end;
