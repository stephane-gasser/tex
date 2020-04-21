procedure writeout(p: halfword);
var
  oldsetting: 0..21;
  oldmode: integer;
  j: smallnumber;
  q, r: halfword;
begin
  {1371:}
q := getavail;
  mem[q].hh.lh := 637;
  r := getavail;
  mem[q].hh.rh := r;
  mem[r].hh.lh := 6717;
  begintokenlist(q, 4);
  begintokenlist(mem[p + 1].hh.rh, 15);
  q := getavail;
  mem[q].hh.lh := 379;
  begintokenlist(q, 4);
  oldmode := curlist.modefield;
  curlist.modefield := 0;
  curcs := writeloc;
  q := scantoks(false, true);
  gettoken;
  if curtok <> 6717 then{1372:}

  begin
    begin
      if interaction = 3 then;
      printnl(262);
      print(1296);
    end;
    begin
      helpptr := 2;
      helpline[1] := 1297;
      helpline[0] := 1011;
    end;
    error;
    repeat
      gettoken;
    until curtok = 6717;
  end{:1372}
;
  curlist.modefield := oldmode;
  endtokenlist{:1371}
;
  oldsetting := selector;
  j := mem[p + 1].hh.lh;
  if writeopen[j] then
    selector := j
  else
  begin
    if (j = 17) and (selector = 19) then
      selector := 18;
    printnl(338);
  end;
  tokenshow(defref);
  println;
  flushlist(defref);
  selector := oldsetting;
end;
