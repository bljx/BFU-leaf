


#include<iostream.h>
void fun(int i){ 
  
   if(i>0) fun(i/2); cout<<i<<endl;
  
}
void main( ){
  fun(10);}
