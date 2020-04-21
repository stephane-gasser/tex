procedure printchar(s: ASCIIcode);
label
  10;
begin
  if{244:}
s = eqtb[5312].int{:244}
 then
    if selector < 20 then
    begin
      println;
      goto 10;
    end;
  case selector of
    19:
    begin
      write(termout, xchr[s]);
      write(logfile, xchr[s]);
      termoffset := termoffset + 1;
      fileoffset := fileoffset + 1;
      if termoffset = maxprintline then
      begin
        writeln(termout);
        termoffset := 0;
      end;
      if fileoffset = maxprintline then
      begin
        writeln(logfile);
        fileoffset := 0;
      end;
    end;
    18:
    begin
      write(logfile, xchr[s]);
      fileoffset := fileoffset + 1;
      if fileoffset = maxprintline then
        println;
    end;
    17:
    begin
      write(termout, xchr[s]);
      termoffset := termoffset + 1;
      if termoffset = maxprintline then
        println;
    end;
    16: ;
    20: if tally < trickcount then
        trickbuf[tally mod errorline] := s;
    21: if poolptr < poolsize then
      begin
        strpool[poolptr] := s;
        poolptr := poolptr + 1;
      end;
    others: write(writefile[selector], xchr[s])
  end;
  tally := tally + 1;
  10: ;
end;{:58}
{59:}

