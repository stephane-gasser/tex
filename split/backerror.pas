procedure backerror;
begin
  OKtointerrupt := false;
  backinput;
  OKtointerrupt := true;
  error;
end;
