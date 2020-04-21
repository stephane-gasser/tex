function bopenin(var f: bytefile): boolean;
begin
  reset(f, nameoffile, '/O');
  bopenin := erstat(f) = 0;
end;

