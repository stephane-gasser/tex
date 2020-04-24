#include "normalparagraph.h"
void normalparagraph(void)
begin
  if eqtb[5282].int <> 0 then
    eqworddefine(5282, 0);
  if eqtb[5847].int <> 0 then
    eqworddefine(5847, 0);
  if eqtb[5304].int <> 1 then
    eqworddefine(5304, 1);
  if eqtb[3412].hh.rh <> 0 then
    eqdefine(3412, 118, 0);
end;
