procedure scanglue(level: smallnumber);
label
  10;
var
  negative: boolean;
  q: halfword;
  mu: boolean;
begin
  mu := (level = 3);
  {441:}
negative := false;
  repeat
    {406:}
repeat
      getxtoken;
    until curcmd <> 10{:406}
;
    if curtok = 3117 then
    begin
      negative := not negative;
      curtok := 3115;
    end;
  until curtok <> 3115{:441}
;
  if (curcmd >= 68) and (curcmd <= 89) then
  begin
    scansomethinginternal(level,
      negative);
    if curvallevel >= 2 then
    begin
      if curvallevel <> level then
        muerror;
      goto 10;
    end;
    if curvallevel = 0 then
      scandimen(mu, false, true)
    else if level = 3 then
      muerror;
  end
  else
  begin
    backinput;
    scandimen(mu, false, false);
    if negative then
      curval := -curval;
  end;
  {462:}
q := newspec(0);
  mem[q + 1].int := curval;
  if scankeyword(730) then
  begin
    scandimen(mu, true, false);
    mem[q + 2].int := curval;
    mem[q].hh.b0 := curorder;
  end;
  if scankeyword(731) then
  begin
    scandimen(mu, true, false);
    mem[q + 3].int := curval;
    mem[q].hh.b1 := curorder;
  end;
  curval := q{:462}
;
  10: ;
end;
