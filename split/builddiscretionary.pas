procedure builddiscretionary;
label
  30, 10;
var
  p, q: halfword;
  n: integer;
begin
  unsave;
  {1121:}
q := curlist.headfield;
  p := mem[q].hh.rh;
  n := 0;
  while p <> 0 do
  begin
    if not (p >= himemmin) then
      if mem[p].hh.b0 > 2 then
        if mem[p].hh.b0 <> 11 then
          if mem[p].hh.b0 <> 6 then
          begin
            begin
              if interaction = 3 then;
              printnl(262);
              print(1106);
            end;
            begin
              helpptr := 1;
              helpline[0] := 1107;
            end;
            error;
            begindiagnostic;
            printnl(1108);
            showbox(p);
            enddiagnostic(true);
            flushnodelist(p);
            mem[q].hh.rh := 0;
            goto 30;
          end;
    q := p;
    p := mem[q].hh.rh;
    n := n + 1;
  end;
  30:
  {:1121}
;
  p := mem[curlist.headfield].hh.rh;
  popnest;
  case savestack[saveptr - 1].int of
    0: mem[curlist.tailfield + 1].hh.lh := p;
    1: mem[curlist.tailfield + 1].hh.rh := p;
    2:{1120:}

    begin
      if (n > 0) and (abs(curlist.modefield) = 203) then
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(1100);
        end;
        printesc(349);
        begin
          helpptr := 2;
          helpline[1] := 1101;
          helpline[0] := 1102;
        end;
        flushnodelist(p);
        n := 0;
        error;
      end
      else
        mem[curlist.tailfield].hh.rh := p;
      if n <= 255 then
        mem[curlist.tailfield].hh.b1 := n
      else
      begin
        begin
          if interaction = 3 then;
          printnl(262);
          print(1103);
        end;
        begin
          helpptr := 2;
          helpline[1] := 1104;
          helpline[0] := 1105;
        end;
        error;
      end;
      if n > 0 then
        curlist.tailfield := q;
      saveptr := saveptr - 1;
      goto 10;
    end{:1120}
;
  end;
  savestack[saveptr - 1].int := savestack[saveptr - 1].int + 1;
  newsavelevel(10);
  scanleftbrace;
  pushnest;
  curlist.modefield := -102;
  curlist.auxfield.hh.lh := 1000;
  10: ;
end;
