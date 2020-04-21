function getnode(s: integer): halfword;
label
  40, 10, 20;
var
  p: halfword;
  q: halfword;
  r: integer;
  t: integer;
begin
  20:
    p := rover;
  repeat
    {127:}
q := p + mem[p].hh.lh;
    while (mem[q].hh.rh = 65535) do
    begin
      t := mem[q + 1].hh.rh;
      if q = rover then
        rover := t;
      mem[t + 1].hh.lh := mem[q + 1].hh.lh;
      mem[mem[q + 1].hh.lh + 1].hh.rh := t;
      q := q + mem[q].hh.lh;
    end;
    r := q - s;
    if r > p + 1 then{128:}

    begin
      mem[p].hh.lh := r - p;
      rover := p;
      goto 40;
    end{:128}
;
    if r = p then
      if mem[p + 1].hh.rh <> p then{129:}

      begin
        rover := mem[p + 1].hh.rh;
        t := mem[p + 1].hh.lh;
        mem[rover + 1].hh.lh := t;
        mem[t + 1].hh.rh := rover;
        goto 40;
      end{:129}
;
    mem[p].hh.lh := q - p{:127}
;
    p := mem[p + 1].hh.rh;
  until p = rover;
  if s = 1073741824 then
  begin
    getnode := 65535;
    goto 10;
  end;
  if lomemmax + 2 < himemmin then
    if lomemmax + 2 <= 65535 then{126:}

    begin
      if himemmin - lomemmax >= 1998 then
        t := lomemmax + 1000
      else
        t := lomemmax + 1 + (himemmin - lomemmax) div 2;
      p := mem[rover + 1].hh.lh;
      q := lomemmax;
      mem[p + 1].hh.rh := q;
      mem[rover + 1].hh.lh := q;
      if t > 65535 then
        t := 65535;
      mem[q + 1].hh.rh := rover;
      mem[q + 1].hh.lh := p;
      mem[q].hh.rh := 65535;
      mem[q].hh.lh := t - lomemmax;
      lomemmax := t;
      mem[lomemmax].hh.rh := 0;
      mem[lomemmax].hh.lh := 0;
      rover := q;
      goto 20;
    end{:126}
;
  overflow(300, memmax + 1 - memmin);
  40:
    mem[r].hh.rh := 0;{varused:=varused+s;}

  getnode := r;
  10: ;
end;
