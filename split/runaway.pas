procedure runaway;
var
  p: halfword;
begin
  if scannerstatus > 1 then
  begin
    printnl(569);
    case scannerstatus of
      2:
      begin
        print(570);
        p := defref;
      end;
      3:
      begin
        print(571);
        p := 29997;
      end;
      4:
      begin
        print(572);
        p := 29996;
      end;
      5:
      begin
        print(573);
        p := defref;
      end;
    end;
    printchar(63);
    println;
    showtokenlist(mem[p].hh.rh, 0, errorline - 10);
  end;
end;
