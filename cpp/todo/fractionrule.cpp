#include "fractionrule.h"
halfword fractionrule(scaled t)
var
  p: halfword;
begin
  p := newrule;
  mem[p + 3].int := t;
  mem[p + 2].int := 0;
  fractionrule := p;
end;
