(*计算两个数的最大公约数*)

var x,y,rem;
begin
  read(x);
  read(y);
  repeat
    rem:=x-y*(x/y);
    x:=y;
    y:=rem
  until rem=0;
  write(x)
end.
