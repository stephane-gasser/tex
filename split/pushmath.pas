procedure pushmath(c: groupcode);
begin
  pushnest;
  curlist.modefield := -203;
  curlist.auxfield.int := 0;
  newsavelevel(c);
end;
