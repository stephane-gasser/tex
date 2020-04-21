function aopenin(var f: alphafile): boolean;
begin
  reset(f, nameoffile, '/O');
  aopenin := erstat(f) = 0;
end;
