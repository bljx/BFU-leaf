#include <iostream.h>
void main(){
	int m,i=0,a[20]={0};
	cin>>m;
	while(m){
     a[i]=m%2;
     m/=2;
     i++;
	}
	for(i=i-1;i>=0;i--)
     cout<<a[i];
	cout<<endl;
}

 