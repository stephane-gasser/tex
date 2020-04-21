procedure insertrelax;
begin
  curtok := 4095 + curcs;
  backinput;
  curtok := 6716;
  backinput;
  curinput.indexfield := 4;
end;
