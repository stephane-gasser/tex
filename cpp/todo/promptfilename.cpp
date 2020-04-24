#include "promptfilename.h"
void promptfilename(strnumber s, strnumber  e)
label
  30;
var
  k: 0..bufsize;
begin
  if interaction = 2 then;
  if s = 786 then
  begin
    if interaction = 3 then;
    printnl(262);
    print(787);
  end
  else
  begin
    if interaction = 3 then;
    printnl(262);
    print(788);
  end;
  printfilename(curname, curarea, curext);
  print(789);
  if e = 790 then
    showcontext;
  printnl(791);
  print(s);
  if interaction < 2 then
    fatalerror(792);
  breakin(termin, true);
  begin
    ;
    print(568);
    terminput;
  end;{531:}

  begin
    beginname;
    k := First;
    while (buffer[k] = 32) and (k < last) do
      k := k + 1;
    while true do
    begin
      if k = last then
        goto 30;
      if not morename(buffer[k]) then
        goto 30;
      k := k + 1;
    end;
    30:
      endname;
  end{:531}
;
  if curext = 338 then
    curext := e;
  packfilename(curname, curarea, curext);
end;
