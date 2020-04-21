function strtoks(b: poolpointer): halfword;
var
  p: halfword;
  q: halfword;
  t: halfword;
  k: poolpointer;
begin
  begin
    if poolptr + 1 > poolsize then
      overflow(257, poolsize - initpoolptr);
  end;
  p := 29997;
  mem[p].hh.rh := 0;
  k := b;
  while k < poolptr do
  begin
    t := strpool[k];
    if t = 32 then
      t := 2592
    else
      t := 3072 + t;
    begin
      begin
        q := avail;
        if q = 0 then
          q := getavail
        else
        begin
          avail := mem[q].hh.rh;
          mem[q].hh.rh := 0;
          {dynused:=dynused+1;}
end;
      end;
      mem[p].hh.rh := q;
      mem[q].hh.lh := t;
      p := q;
    end;
    k := k + 1;
  end;
  poolptr := b;
  strtoks := p;
end;

