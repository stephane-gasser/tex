#include "openfmtfile.h"
bool openfmtfile(void)
label
  40, 10;
var
  j: 0..bufsize;
{
  j = curinput.locfield;
  if (buffer[curinput.locfield] == 38)
  {
    curinput.locfield = curinput.locfield+1;
    j = curinput.locfield;
    buffer[last] = 32;
    while buffer[j] != 32 do
      j = j+1;
    packbufferedname(0, curinput.locfield, j-1);
    if (wopenin(fmtfile))
      goto 40;
    packbufferedname(11, curinput.locfield, j-1);
    if (wopenin(fmtfile))
      goto 40;
    ;
    writeln(termout, 'Sorry, I can''t find that format;', ' will try PLAIN.');
    break(termout);
  }
  packbufferedname(16, 1, 0);
  if (not wopenin(fmtfile))
  {
    ;
    writeln(termout, 'I can''t find the PLAIN format file!');
    openfmtfile = false;
    goto 10;
  }
  40:
    curinput.locfield = j;
  openfmtfile = true;
  10: ;
}
