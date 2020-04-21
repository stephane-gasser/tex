function wopenin(var f: wordfile): boolean;
begin
  reset(f, nameoffile, '/O');
  wopenin := erstat(f) = 0;
end;
