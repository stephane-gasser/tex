procedure initspan(p: halfword);
begin
  pushnest;
  if curlist.modefield = -102 then
    curlist.auxfield.hh.lh := 1000
  else
  begin
    curlist.auxfield.int := -65536000;
    normalparagraph;
  end;
  curspan := p;
end;
