function wopenout(var f: wordfile): boolean;
begin
  rewrite(f, nameoffile, '/O');
  wopenout := erstat(f) = 0;
end;
