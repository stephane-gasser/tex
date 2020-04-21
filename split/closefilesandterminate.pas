procedure closefilesandterminate;
var
  k: integer;
begin
  {1378:}
for k := 0 to 15 do
    if writeopen[k] then
      aclose(writefile[k])
  {:1378}
;
{if eqtb[5294].int>0 then[1334:]if logopened then begin writeln(logfile,
' ');writeln(logfile,'Here is how much of TeX''s memory',' you used:');
write(logfile,' ',strptr-initstrptr:1,' string');
if strptr<>initstrptr+1 then write(logfile,'s');
writeln(logfile,' out of ',maxstrings-initstrptr:1);
writeln(logfile,' ',poolptr-initpoolptr:1,' string characters out of ',
poolsize-initpoolptr:1);
writeln(logfile,' ',lomemmax-memmin+memend-himemmin+2:1,
' words of memory out of ',memend+1-memmin:1);
writeln(logfile,' ',cscount:1,' multiletter control sequences out of ',
2100:1);
write(logfile,' ',fmemptr:1,' words of font info for ',fontptr-0:1,
' font');if fontptr<>1 then write(logfile,'s');
writeln(logfile,', out of ',fontmemsize:1,' for ',fontmax-0:1);
write(logfile,' ',hyphcount:1,' hyphenation exception');
if hyphcount<>1 then write(logfile,'s');
writeln(logfile,' out of ',307:1);
writeln(logfile,' ',maxinstack:1,'i,',maxneststack:1,'n,',maxparamstack:
1,'p,',maxbufstack+1:1,'b,',maxsavestack+6:1,'s stack positions out of '
,stacksize:1,'i,',nestsize:1,'n,',paramsize:1,'p,',bufsize:1,'b,',
savesize:1,'s');end[:1334];}
;
  {642:}
while curs > -1 do
  begin
    if curs > 0 then
    begin
      dvibuf[dviptr] := 142;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end
    else
    begin
      begin
        dvibuf[dviptr] := 140;
        dviptr := dviptr + 1;
        if dviptr = dvilimit then
          dviswap;
      end;
      totalpages := totalpages + 1;
    end;
    curs := curs - 1;
  end;
  if totalpages = 0 then
    printnl(836)
  else
  begin
    begin
      dvibuf[dviptr] := 248;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    dvifour(lastbop);
    lastbop := dvioffset + dviptr - 5;
    dvifour(25400000);
    dvifour(473628672);
    preparemag;
    dvifour(eqtb[5280].int);
    dvifour(maxv);
    dvifour(maxh);
    begin
      dvibuf[dviptr] := maxpush div 256;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    begin
      dvibuf[dviptr] := maxpush mod 256;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    begin
      dvibuf[dviptr] := (totalpages div 256) mod 256;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    begin
      dvibuf[dviptr] := totalpages mod 256;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    {643:}
while fontptr > 0 do
    begin
      if fontused[fontptr] then
        dvifontdef(
          fontptr);
      fontptr := fontptr - 1;
    end{:643}
;
    begin
      dvibuf[dviptr] := 249;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    dvifour(lastbop);
    begin
      dvibuf[dviptr] := 2;
      dviptr := dviptr + 1;
      if dviptr = dvilimit then
        dviswap;
    end;
    k := 4 + ((dvibufsize - dviptr) mod 4);
    while k > 0 do
    begin
      begin
        dvibuf[dviptr] := 223;
        dviptr := dviptr + 1;
        if dviptr = dvilimit then
          dviswap;
      end;
      k := k - 1;
    end;
    {599:}
if dvilimit = halfbuf then
      writedvi(halfbuf, dvibufsize - 1);
    if dviptr > 0 then
      writedvi(0, dviptr - 1){:599}
;
    printnl(837);
    slowprint(outputfilename);
    print(286);
    printint(totalpages);
    print(838);
    if totalpages <> 1 then
      printchar(115);
    print(839);
    printint(dvioffset + dviptr);
    print(840);
    bclose(dvifile);
  end{:642}
;
  if logopened then
  begin
    writeln(logfile);
    aclose(logfile);
    selector := selector - 2;
    if selector = 17 then
    begin
      printnl(1274);
      slowprint(logname);
      printchar(46);
    end;
  end;
end;
