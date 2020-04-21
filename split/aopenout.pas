function aopenout(var f: alphafile): boolean;
begin
  rewrite(f, nameoffile, '/O');
  aopenout := erstat(f) = 0;
end;
