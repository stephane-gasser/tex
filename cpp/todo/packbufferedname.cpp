#include "packbufferedname.h"
void packbufferedname(smallnumber n, int a, int  b)
var
  k: integer;
  c: ASCIIcode;
  j: integer;
begin
  if n + b - a + 5 > filenamesize then
    b := a + filenamesize - n - 5;
  k := 0;
  for j := 1 to n do
  begin
    c := xord[TEXformatdefault[j]];
    k := k + 1;
    if k <= filenamesize then
      nameoffile[k] := xchr[c];
  end;
  for j := a to b do
  begin
    c := buffer[j];
    k := k + 1;
    if k <= filenamesize then
      nameoffile[k] := xchr[c];
  end;
  for j := 17 to 20 do
  begin
    c := xord[TEXformatdefault[j]];
    k := k + 1;
    if k <= filenamesize then
      nameoffile[k] := xchr[c];
  end;
  if k <= filenamesize then
    namelength := k
  else
    namelength := filenamesize;
  for k := namelength + 1 to filenamesize do
    nameoffile[k] := ' ';
end;
