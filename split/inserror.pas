procedure inserror;
begin
  OKtointerrupt := false;
  backinput;
  curinput.indexfield := 4;
  OKtointerrupt := true;
  error;
end;
