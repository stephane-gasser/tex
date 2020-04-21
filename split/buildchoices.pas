procedure buildchoices;
label
  10;
var
  p: halfword;
begin
  unsave;
  p := finmlist(0);
  case savestack[saveptr - 1].int of
    0: mem[curlist.tailfield + 1].hh.lh := p;
    1: mem[curlist.tailfield + 1].hh.rh := p;
    2: mem[curlist.tailfield + 2].hh.lh := p;
    3:
    begin
      mem[curlist.tailfield + 2].hh.rh := p;
      saveptr := saveptr - 1;
      goto 10;
    end;
  end;
  savestack[saveptr - 1].int := savestack[saveptr - 1].int + 1;
  pushmath(13);
  scanleftbrace;
  10: ;
end;
