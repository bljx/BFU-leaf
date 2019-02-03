const pi=3;
var r,s;
procedure area;
  var r1;
  begin
    r1:=r*r;s:=pi*r1
  end;
begin
  read(r);
  if r>10 then call area;
  write(s)  
end.