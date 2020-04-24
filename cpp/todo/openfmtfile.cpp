#include "openfmtfile.h"
bool openfmtfile(void)
label
  40, 10;
var
  j: 0..bufsize;
begin
  j := curinput.locfield;
  if buffer[curinput.locfield] = 38 then
  begin
    curinput.locfield := curinput.locfield + 1;
    j := curinput.locfield;
    buffer[last] := 32;
    while buffer[j] <> 32 do
      j := j + 1;
    packbufferedname(0, curinput.locfield, j - 1);
    if wopenin(fmtfile) then
      goto 40;
    packbufferedname(11, curinput.locfield, j - 1);
    if wopenin(fmtfile) then
      goto 40;
    ;
    writeln(termout, 'Sorry, I can''t find that format;', ' will try PLAIN.');
    break(termout);
  end;
  packbufferedname(16, 1, 0);
  if not wopenin(fmtfile) then
  begin
    ;
    writeln(termout, 'I can''t find the PLAIN format file!');
    openfmtfile := false;
    goto 10;
  end;
  40:
    curinput.locfield := j;
  openfmtfile := true;
  10: ;
end;
