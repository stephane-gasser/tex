function idlookup(j, l: integer): halfword;
label
  40;
var
  h: integer;
  d: integer;
  p: halfword;
  k: halfword;
begin
  {261:}
h := buffer[j];
  for k := j + 1 to j + l - 1 do
  begin
    h := h + h + buffer[k];
    while h >= 1777 do
      h := h - 1777;
  end{:261}
;
  p := h + 514;
  while true do
  begin
    if hash[p].rh > 0 then
      if (strstart[hash[p].rh + 1] - strstart[hash[p].rh]) = l then
        if streqbuf(hash[p].rh, j) then
          goto 40;
    if hash[p].lh = 0 then
    begin
      if nonewcontrolsequence then
        p := 2881
      else
        {260:}
begin
        if hash[p].rh > 0 then
        begin
          repeat
            if (hashused = 514) then
              overflow(503, 2100);
            hashused := hashused - 1;
          until hash[hashused].rh = 0;
          hash[p].lh := hashused;
          p := hashused;
        end;
        begin
          if poolptr + l > poolsize then
            overflow(257, poolsize - initpoolptr);
        end;
        d := (poolptr - strstart[strptr]);
        while poolptr > strstart[strptr] do
        begin
          poolptr := poolptr - 1;
          strpool[poolptr + l] := strpool[poolptr];
        end;
        for k := j to j + l - 1 do
        begin
          strpool[poolptr] := buffer[k];
          poolptr := poolptr + 1;
        end;
        hash[p].rh := makestring;
        poolptr := poolptr + d;
        {cscount:=cscount+1;}
end{:260}
;
      goto 40;
    end;
    p := hash[p].lh;
  end;
  40:
    idlookup := p;
end;
