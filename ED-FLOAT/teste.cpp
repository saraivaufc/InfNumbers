#include <iostream>
#include <cstdlib>
#include "lista.h"
#include "infnumber.h"

using namespace std;

int main(){
		{
		char a[]="123,3";
		char b[]="20.1";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * c=InfSum(x,y);
		cout<<endl;
		InfPrint(x);
		cout<<endl;
		InfPrint(y); 
		cout<<"\n";InfPrint(c);
		
	}
	return 0;
}



