procedure triefix(p: triepointer);
var
  q: triepointer;
  c: ASCIIcode;
  z: triepointer;
begin
  z := triehash[p];
  repeat
    q := triel[p];
    c := triec[p];
    trie[z + c].rh := triehash[q];
    trie[z + c].b1 := c + 0;
    trie[z + c].b0 := trieo[p];
    if q > 0 then
      triefix(q);
    p := trier[p];
  until p = 0;
end;
