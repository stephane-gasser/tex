#include "printtotals.h"
void printtotals(void)
begin
  printscaled(pagesofar[1]);
  if pagesofar[2] <> 0 then
  begin
    print(312);
    printscaled(pagesofar[2]);
    print(338);
  end;
  if pagesofar[3] <> 0 then
  begin
    print(312);
    printscaled(pagesofar[3]);
    print(311);
  end;
  if pagesofar[4] <> 0 then
  begin
    print(312);
    printscaled(pagesofar[4]);
    print(977);
  end;
  if pagesofar[5] <> 0 then
  begin
    print(312);
    printscaled(pagesofar[5]);
    print(978);
  end;
  if pagesofar[6] <> 0 then
  begin
    print(313);
    printscaled(pagesofar[6]);
  end;
end;
