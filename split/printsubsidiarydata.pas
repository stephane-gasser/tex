procedure printsubsidiarydata(p: halfword; c: ASCIIcode);
begin
  if (poolptr - strstart[strptr]) >= depththreshold then
  begin
    if mem[p].hh.rh <> 0 then
      print(314);
  end
  else
  begin
    begin
      strpool[poolptr] := c;
      poolptr := poolptr + 1;
    end;
    tempptr := p;
    case mem[p].hh.rh of
      1:
      begin
        println;
        printcurrentstring;
        printfamandchar(p);
      end;
      2: showinfo;
      3: if mem[p].hh.lh = 0 then
        begin
          println;
          printcurrentstring;
          print(859);
        end
        else
          showinfo;
      others: end;
    poolptr := poolptr - 1;
  end;
end;

