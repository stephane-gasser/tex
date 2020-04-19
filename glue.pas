{2:}program GLUE(input, output);

type
  {6:}glueratio = packed record
    apart: 1..31;
    bpart: 0..30;
    cpart: 0..32768;
  end;
  scaled = integer;{:6}
var
  {8:}twotothe: array[0..30] of integer;
  {:8}{15:}dig: array[0..15] of 0..9;
  {:15}{20:}x: array[1..1000] of scaled;
  t: scaled;
  m: integer;{:20}

procedure Initialize;
var
  {9:}k: 1..30;
  {:9}begin
  {10:}twotothe[0] := 1;
  for k := 1 to 30 do
    twotothe[k] := twotothe[k - 1] + twotothe[k - 1];
  {:10};
end;

{:2}{11:}
function gluemult(x: scaled; g: glueratio): integer;
begin
  if g.apart > 16 then
    x := x div twotothe[g.apart - 16]
  else
    x := x * twotothe[16 - g.apart];
  gluemult := (x * g.cpart) div twotothe[g.bpart];
end;

{:11}{12:}
procedure gluefix(s, t, y: scaled; var g: glueratio);
var
  a, b, c: integer;
  k, h: integer;
  s0: integer;
  q, r, s1: integer;
  w: integer;
begin{13:}
  begin
    a := 15;
    k := 0;
    h := 0;
    s0 := s;
    while y < 1073741824 do
    begin
      a := a - 1;
      y := y + y;
    end;
    while s < 1073741824 do
    begin
      k := k + 1;
      s := s + s;
    end;
    while t < 1073741824 do
    begin
      h := h + 1;
      t := t + t;
    end;
  end{:13};
  if t < s then
    b := 15 - a - k + h
  else
    b := 14 - a - k + h;
  if (b < 0) or (b > 30) then
  begin
    if b < 0 then
      writeln('! Excessive glue.');
    b := 0;
    c := 0;
  end
  else if k >= 16 then
    c := (t div twotothe[h - a - b] + s0 - 1) div s0
  else
    {14:}begin
    w := twotothe[16 - k];
    s1 := s0 div w;
    q := t div s1;
    r := ((t mod s1) * w) - ((s0 mod w) * q);
    if r > 0 then
    begin
      q := q + 1;
      r := r - s0;
    end
    else
      while r <= -s0 do
      begin
        q := q - 1;
        r := r + s0;
      end;
    if a + b + k - h = 15 then
      c := (q + 1) div 2
    else
      c := (q + 3) div 4;
  end{:14};
  g.apart := a + 16;
  g.bpart := b;
  g.cpart := c;
end;

{:12}{16:}
procedure printdigs(k: integer);
begin
  while k > 0 do
  begin
    k := k - 1;
    write(chr(Ord('0') + dig[k]));
  end;
end;

{:16}{17:}
procedure printint(n: integer);
var
  k: 0..12;
begin
  k := 0;
  repeat
    dig[k] := n mod 10;
    n := n div 10;
    k := k + 1;
  until n = 0;
  printdigs(k);
end;

{:17}{18:}
procedure printscaled(s: scaled);
var
  k: 0..3;
begin
  printint(s div 65536);
  s := ((s mod 65536) * 10000) div 65536;
  for k := 0 to 3 do
  begin
    dig[k] := s mod 10;
    s := s div 10;
  end;
  write('.');
  printdigs(4);
end;{:18}{19:}

procedure printgr(g: glueratio);
var
  j: -29..31;
begin
  j := 32 - g.apart - g.bpart;
  while j > 15 do
  begin
    write('2x');
    j := j - 1;
  end;
  if j < 0 then
    printscaled(g.cpart div twotothe[-j])
  else
    printscaled(g.cpart * twotothe[j]);
end;{:19}{21:}

procedure test;
var
  n: 0..1000;
  k: 0..1000;
  y: scaled;
  g: glueratio;
  s: scaled;
  ts: scaled;
begin
  writeln('Test data set number ', m: 1, ':');{22:}
  begin
    n := 0;
    repeat
      n := n + 1;
      read(x[n]);
    until x[n] = 0;
    n := n - 1;
  end{:22};{23:}
  begin
    s := 0;
    y := 0;
    for k := 1 to n do
    begin
      s := s + x[k];
      if y < abs(x[k]) then
        y := abs(x[k]);
    end;
  end{:23};
  if s <= 0 then
    writeln(
      'Invalid data (nonpositive sum); this set rejected.')
  else
  begin{24:}
    begin
      gluefix(s, t, y, g);
      write('  Glue ratio is ');
      printgr(g);
      writeln(' (', g.apart - 16: 1, ',', g.bpart: 1, ',', g.cpart: 1, ')');
    end{:24};
    {25:}begin
      ts := 0;
      for k := 1 to n do
      begin
        write(x[k]: 20);
        if x[k] >= 0 then
          y := gluemult(x[k], g)
        else
          y := -gluemult(-x[k], g);
        writeln(y: 15);
        ts := ts + y;
      end;
      writeln(' Totals', s: 13, ts: 15, ' (versus ', t: 1, ')');
    end{:25};
  end;
end;

{:21}{26:}begin
  Initialize;
  m := 1;
  read(t);
  while t > 0 do
  begin
    test;
    m := m + 1;
    read(t);
  end;
end.
{:26}
