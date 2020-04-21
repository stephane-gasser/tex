procedure startinput;
label
  30;
begin
  scanfilename;
  if curext = 338 then
    curext := 790;
  packfilename(curname, curarea, curext);
  while true do
  begin
    beginfilereading;
    if aopenin(inputfile[curinput.indexfield]) then
      goto 30;
    if curarea = 338 then
    begin
      packfilename(curname, 783, curext);
      if aopenin(inputfile[curinput.indexfield]) then
        goto 30;
    end;
    endfilereading;
    promptfilename(786, 790);
  end;
  30:
    curinput.namefield := amakenamestring(inputfile[curinput.indexfield]);
  if jobname = 0 then
  begin
    jobname := curname;
    openlogfile;
  end;
  if termoffset + (strstart[curinput.namefield + 1] - strstart[curinput.namefield]) > maxprintline - 2 then
    println
  else if (termoffset > 0) or (fileoffset > 0) then
    printchar(32);
  printchar(40);
  openparens := openparens + 1;
  slowprint(curinput.namefield);
  break(termout);
  curinput.statefield := 33;
  if curinput.namefield = strptr - 1 then
  begin
    begin
      strptr := strptr - 1;
      poolptr := strstart[strptr];
    end;
    curinput.namefield := curname;
  end;
  {538:}
begin
    line := 1;
    if inputln(inputfile[curinput.indexfield], false) then;
    firmuptheline;
    if (eqtb[5311].int < 0) or (eqtb[5311].int > 255) then
      curinput.limitfield :=
        curinput.limitfield - 1
    else
      buffer[curinput.limitfield] := eqtb[5311].int;
    First := curinput.limitfield + 1;
    curinput.locfield := curinput.startfield;
  end{:538}
;
end;
