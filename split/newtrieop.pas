function newtrieop(d, n: smallnumber; v: quarterword): quarterword;
label
  10;
var
  h: -trieopsize..trieopsize;
  u: quarterword;
  l: 0..trieopsize;
begin
  h := abs(n + 313 * d + 361 * v + 1009 * curlang) mod (trieopsize + trieopsize) - trieopsize;
  while true do
  begin
    l := trieophash[h];
    if l = 0 then
    begin
      if trieopptr = trieopsize then
        overflow(948, trieopsize);
      u := trieused[curlang];
      if u = 255 then
        overflow(949, 255);
      trieopptr := trieopptr + 1;
      u := u + 1;
      trieused[curlang] := u;
      hyfdistance[trieopptr] := d;
      hyfnum[trieopptr] := n;
      hyfnext[trieopptr] := v;
      trieoplang[trieopptr] := curlang;
      trieophash[h] := trieopptr;
      trieopval[trieopptr] := u;
      newtrieop := u;
      goto 10;
    end;
    if (hyfdistance[l] = d) and (hyfnum[l] = n) and (hyfnext[l] = v) and (trieoplang[l] = curlang) then
    begin
      newtrieop := trieopval[l];
      goto 10;
    end;
    if h > -trieopsize then
      h := h - 1
    else
      h := trieopsize;
  end;
  10: ;
end;
