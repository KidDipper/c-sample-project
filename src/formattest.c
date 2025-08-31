#include <stdio.h>
int*add ( int a,int b ){int result=a+b;   return &result; }

int main(){
int x=1;int y=2;
 int* z=add(x,y);printf("sum=%d\n",*z);
return 0;}
