const a=10;
var b,c;
procedure p;

  begin
    c:=b+a
  end;
begin
  read(b);
  while b#0 do
    begin
      call p; write(2*c); read(b)
    end
end.
