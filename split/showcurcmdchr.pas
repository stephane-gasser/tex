procedure showcurcmdchr;
begin
  begindiagnostic;
  printnl(123);
  if curlist.modefield <> shownmode then
  begin
    printmode(curlist.modefield);
    print(568);
    shownmode := curlist.modefield;
  end;
  printcmdchr(curcmd, curchr);
  printchar(125);
  enddiagnostic(false);
end;
