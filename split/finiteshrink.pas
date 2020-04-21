function finiteshrink(p: halfword): halfword;
var
  q: halfword;
begin
  if noshrinkerroryet then
  begin
    noshrinkerroryet := false;
    begin
      if interaction = 3 then;
      printnl(262);
      print(916);
    end;
    begin
      helpptr := 5;
      helpline[4] := 917;
      helpline[3] := 918;
      helpline[2] := 919;
      helpline[1] := 920;
      helpline[0] := 921;
    end;
    error;
  end;
  q := newspec(p);
  mem[q].hh.b1 := 0;
  deleteglueref(p);
  finiteshrink := q;
end;
