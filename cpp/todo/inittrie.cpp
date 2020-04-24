#include "inittrie.h"
void inittrie(void)
var
  p: triepointer;
  j, k, t: integer;
  r, s: triepointer;
  h: twohalves;
begin
  {952:}
{945:}
opstart[0] := -0;
  for j := 1 to 255 do
    opstart[j] := opstart[j - 1] + trieused[j - 1] - 0;
  for j := 1 to trieopptr do
    trieophash[j] := opstart[trieoplang[j]] + trieopval[j];
  for j := 1 to trieopptr do
    while trieophash[j] > j do
    begin
      k := trieophash[j];
      t := hyfdistance[k];
      hyfdistance[k] := hyfdistance[j];
      hyfdistance[j] := t;
      t := hyfnum[k];
      hyfnum[k] := hyfnum[j];
      hyfnum[j] := t;
      t := hyfnext[k];
      hyfnext[k] := hyfnext[j];
      hyfnext[j] := t;
      trieophash[j] := trieophash[k];
      trieophash[k] := k;
    end{:945}
;
  for p := 0 to triesize do
    triehash[p] := 0;
  triel[0] := compresstrie(triel[0]);
  for p := 0 to trieptr do
    triehash[p] := 0;
  for p := 0 to 255 do
    triemin[p] := p + 1;
  trie[0].rh := 1;
  triemax := 0{:952}
;
  if triel[0] <> 0 then
  begin
    firstfit(triel[0]);
    triepack(triel[0]);
  end;
  {958:}
h.rh := 0;
  h.b0 := 0;
  h.b1 := 0;
  if triel[0] = 0 then
  begin
    for r := 0 to 256 do
      trie[r] := h;
    triemax := 256;
  end
  else
  begin
    triefix(triel[0]);
    r := 0;
    repeat
      s := trie[r].rh;
      trie[r] := h;
      r := s;
    until r > triemax;
  end;
  trie[0].b1 := 63;
  {:958}
;
  trienotready := false;
end;
