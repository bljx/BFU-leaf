(*fibonacci.pl*)
const n=20;
var f1,f2,f,i;
begin
  f1:=1;
  f2:=1;
  i:=1;
  while i<=n do
    begin
	  write(f1);
	  f:=f1+f2;
	  f1:=f2;
	  f2:=f;
	  i:=i+1
	end
end.