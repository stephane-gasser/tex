procedure package(c: smallnumber);
var
  h: scaled;
  p: halfword;
  d: scaled;
begin
  d := eqtb[5837].int;
  unsave;
  saveptr := saveptr - 3;
  if curlist.modefield = -102 then
    curbox := hpack(mem[curlist.headfield].hh.rh, savestack[saveptr + 2].int, savestack[saveptr + 1].int)
  else
  begin
    curbox :=
      vpackage(mem[curlist.headfield].hh.rh, savestack[saveptr + 2].int, savestack[saveptr + 1].int, d);
    if c = 4 then{1087:}

    begin
      h := 0;
      p := mem[curbox + 5].hh.rh;
      if p <> 0 then
        if mem[p].hh.b0 <= 2 then
          h := mem[p + 3].int;
      mem[curbox + 2].int := mem[curbox + 2].int - h + mem[curbox + 3].int;
      mem[curbox + 3].int := h;
    end{:1087}
;
  end;
  popnest;
  boxend(savestack[saveptr + 0].int);
end;
