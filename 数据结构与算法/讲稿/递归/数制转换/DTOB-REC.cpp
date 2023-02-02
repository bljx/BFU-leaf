
#include<iostream.h>

void conversion(int n)
{
	if(n==0)
		return ;
	else
	{
		conversion(n/2);
		cout<<n%2;
	}
}

/*OK	
	if(n==1)
		cout<<n%2; 
	else
	{
		conversion(n/2);
		cout<<n%2;
	}

*/
		
/*OK	
	if(n>0)
	{
		conversion(n/2);
		cout<<n%2;
	}
	return ;
*/

	
	/*  error
	if(n==0)
		return ;
	else
	{
		n=n/2;
		conversion(n);
		cout<<n%2;
	}*/


	/*OK
	if(n==0)
		return ;
	else
	{
		int i=n%2;
		conversion(n/2);
		cout<<i;
	}*/

void main()
{
	int n;
	cin>>n;
	conversion(n);
	cout<<endl;
}

