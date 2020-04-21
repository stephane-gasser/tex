procedure firstfit(p: triepointer);
label
  45, 40;
var
  h: triepointer;
  z: triepointer;
  q: triepointer;
  c: ASCIIcode;
  l, r: triepointer;
  ll: 1..256;
begin
  c := triec[p];
  z := triemin[c];
  while true do
  begin
    h := z - c;
    {954:}
if triemax < h + 256 then
    begin
      if triesize <= h + 256 then
        overflow(950,
          triesize);
      repeat
        triemax := triemax + 1;
        trietaken[triemax] := false;
        trie[triemax].rh := triemax + 1;
        trie[triemax].lh := triemax - 1;
      until triemax = h + 256;
    end{:954}
;
    if trietaken[h] then
      goto 45;
    {955:}
q := trier[p];
    while q > 0 do
    begin
      if trie[h + triec[q]].rh = 0 then
        goto 45;
      q := trier[q];
    end;
    goto 40{:955}
;
    45:
      z := trie[z].rh;
  end;
  40:
    {956:}
trietaken[h] := true;
  triehash[p] := h;
  q := p;
  repeat
    z := h + triec[q];
    l := trie[z].lh;
    r := trie[z].rh;
    trie[r].lh := l;
    trie[l].rh := r;
    trie[z].rh := 0;
    if l < 256 then
    begin
      if z < 256 then
        ll := z
      else
        ll := 256;
      repeat
        triemin[l] := r;
        l := l + 1;
      until l = ll;
    end;
    q := trier[q];
  until q = 0{:956}
;
end;
