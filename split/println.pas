procedure println;
begin
  case selector of
    19:
    begin
      writeln(termout);
      writeln(logfile);
      termoffset := 0;
      fileoffset := 0;
    end;
    18:
    begin
      writeln(logfile);
      fileoffset := 0;
    end;
    17:
    begin
      writeln(termout);
      termoffset := 0;
    end;
    16, 20, 21: ;
    others: writeln(writefile[selector])
  end;
end;

