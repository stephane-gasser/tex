begin
  history := 3;
  rewrite(termout, 'TTY:', '/O');
  if readyalready = 314159 then
    goto 1;
  {14:}
bad := 0;
  if (halferrorline < 30) or (halferrorline > errorline - 15) then
    bad := 1;
  if maxprintline < 60 then
    bad := 2;
  if dvibufsize mod 8 <> 0 then
    bad := 3;
  if 1100 > 30000 then
    bad := 4;
  if 1777 > 2100 then
    bad := 5;
  if maxinopen >= 128 then
    bad := 6;
  if 30000 < 267 then
    bad := 7;
  {:14}
{111:}
if (memmin <> 0) or (memmax <> 30000) then
    bad := 10;
  if (memmin > 0) or (memmax < 30000) then
    bad := 10;
  if (0 > 0) or (255 < 127) then
    bad := 11;
  if (0 > 0) or (65535 < 32767) then
    bad := 12;
  if (0 < 0) or (255 > 65535) then
    bad := 13;
  if (memmin < 0) or (memmax >= 65535) or (-0 - memmin > 65536) then
    bad := 14;
  if (0 < 0) or (fontmax > 255) then
    bad := 15;
  if fontmax > 256 then
    bad := 16;
  if (savesize > 65535) or (maxstrings > 65535) then
    bad := 17;
  if bufsize > 65535 then
    bad := 18;
  if 255 < 255 then
    bad := 19;
  {:111}
{290:}
if 6976 > 65535 then
    bad := 21;
  {:290}
{522:}
if 20 > filenamesize then
    bad := 31;
  {:522}
{1249:}
if 2 * 65535 < 30000 - memmin then
    bad := 41;
  {:1249}
if bad > 0 then
  begin
    writeln(termout,
      'Ouch---my internal constants have been clobbered!', '---case ', bad: 1);
    goto 9999;
  end;
  Initialize;
  if not getstringsstarted then
    goto 9999;
  initprim;
  initstrptr := strptr;
  initpoolptr := poolptr;
  fixdateandtime;
  readyalready := 314159;
  1:
    {55:}
selector := 17;
  tally := 0;
  termoffset := 0;
  fileoffset := 0;
  {:55}
{61:}
write(termout, 'This is TeX, Version 3.14159265');
  if formatident = 0 then
    writeln(termout, ' (no format preloaded)')
  else
  begin
    slowprint(formatident);
    println;
  end;
  break(termout);
  {:61}
{528:}
jobname := 0;
  nameinprogress := false;
  logopened := false;
  {:528}
{533:}
outputfilename := 0;
  {:533}
;
  {1337:}
begin{331:}

    begin
      inputptr := 0;
      maxinstack := 0;
      inopen := 0;
      openparens := 0;
      maxbufstack := 0;
      paramptr := 0;
      maxparamstack := 0;
      First := bufsize;
      repeat
        buffer[First] := 0;
        First := First - 1;
      until First = 0;
      scannerstatus := 0;
      warningindex := 0;
      First := 1;
      curinput.statefield := 33;
      curinput.startfield := 1;
      curinput.indexfield := 0;
      line := 0;
      curinput.namefield := 0;
      forceeof := false;
      alignstate := 1000000;
      if not initterminal then
        goto 9999;
      curinput.limitfield := last;
      First := last + 1;
    end{:331}
;
    if (formatident = 0) or (buffer[curinput.locfield] = 38) then
    begin
      if formatident <> 0 then
        Initialize;
      if not openfmtfile then
        goto 9999;
      if not loadfmtfile then
      begin
        wclose(fmtfile);
        goto 9999;
      end;
      wclose(fmtfile);
      while (curinput.locfield < curinput.limitfield) and (buffer[curinput.locfield] = 32) do
        curinput.locfield := curinput.locfield + 1;
    end;
    if (eqtb[5311].int < 0) or (eqtb[5311].int > 255) then
      curinput.limitfield :=
        curinput.limitfield - 1
    else
      buffer[curinput.limitfield] := eqtb[5311].int;
    fixdateandtime;
    {765:}
magicoffset := strstart[891] - 9 * 16{:765}
;
    {75:}
if interaction = 0 then
      selector := 16
    else
      selector := 17{:75}
;
    if (curinput.locfield < curinput.limitfield) and (eqtb[3983 + buffer[curinput.locfield]].hh.rh <> 0) then
      startinput;
  end{:1337}
;
  history := 0;
  maincontrol;
  finalcleanup;
  9998:
    closefilesandterminate;
  9999:
    readyalready := 0;
end.
