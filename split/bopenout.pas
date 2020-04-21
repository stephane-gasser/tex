function bopenout(var f: bytefile): boolean;
begin
  rewrite(f, nameoffile, '/O');
  bopenout := erstat(f) = 0;
end;
