var x,y,z;
procedure gcd;
	var f,g;
	begin
		f:=x;
		g:=y;
		while f#g do 
			begin 
				if f<g then 
					g:=g-f;
				if g<f then 
					f:=f-g;
			end;
		z:=f
	end;
begin
	x:=84;y:=36;call gcd;write(z)
end.
