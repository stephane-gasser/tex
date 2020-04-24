#include "heightplusdepth.h"
scaled heightplusdepth(internalfontnumber f, quarterword c)
var
  q: fourquarters;
  hd: eightbits;
begin
  q := fontinfo[charbase[f] + c].qqqq;
  hd := q.b1 - 0;
  heightplusdepth := fontinfo[heightbase[f] + (hd) div 16].int + fontinfo[depthbase[f] + (hd) mod 16].int;
end;
