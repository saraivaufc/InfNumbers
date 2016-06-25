#include <iostream>
#include <cstdlib>
#include "lista.h"
#include "infnumber.h"
#include "engine.cpp"

using namespace std;
 
Tester t;

void testa_InfSum(){
	t.open("InfSum:" , 3);
	{
		char a[]="1";
		char b[]="2";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("3");
		res->numbers->sinal='+';
		t.add( InfCompare(InfSum(x,y), res));
	}
	{
		char a[]="2";
		char b[]="1";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("3");
		res->numbers->sinal='+';
		t.add( InfCompare(InfSum(x,y), res));
	}
	{
		char a[]="1";
		char b[]="-2";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("1");
		res->numbers->sinal='-';
		InfNumber * s=InfSum(x,y);
		t.add( InfCompare( s , res));
	}
	{
		char a[]="-1";
		char b[]="2";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("1");
		res->numbers->sinal='+';
		InfNumber * s=InfSum(x,y);
		t.add(InfCompare( s , res));
	}
	{
		char a[]="19";
		char b[]="4";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("23");
		res->numbers->sinal='+';
		t.add( InfCompare(InfSum(x,y), res));
		InfPrint(InfSum(x,y));
	}
	
	{
		char a[]="-1234324324234234234233333333333";
		char b[]="29469236492639462946239649234923649";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("29468002168315228712005415901590316");
		res->numbers->sinal='+';
		InfNumber * s=InfSum(x,y);
		t.add( InfCompare( s , res));
	}
	{
		char a[]="1234324324234234234233333333333";
		char b[]="-29469236492639462946239649234923649";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("29468002168315228712005415901590316");
		res->numbers->sinal='-';
		InfNumber * s=InfSum(x,y);
		t.add( InfCompare( s , res));
	}
	t.close();
}

void teste_InfSub(){
	t.open("InfSub:",5);
	{
		char a[]="2";
		char b[]="1";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("1");
		res->numbers->sinal='+';
		t.add( InfCompare(InfSub(x,y), res));
	}
	{
		char a[]="1";
		char b[]="2";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("1");
		res->numbers->sinal='-';
		t.add( InfCompare(InfSub(x,y), res));
	}
	{
		char a[]="1";
		char b[]="-2";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("3");
		res->numbers->sinal='+';
		t.add( InfCompare(InfSub(x,y), res));
	}
	{
		char a[]="-1";
		char b[]="2";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("3");
		res->numbers->sinal='-';
		t.add( InfCompare(InfSub(x,y), res));
	}
	{
		char a[]="1739173961923619623916293619263";
		char b[]="371936195319531953913193619";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("1738802025728300091962380425644");
		res->numbers->sinal='+';
		t.add( InfCompare(InfSub(x,y), res));
	}
	{
		char a[]="-19";
		char b[]="4";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("23");
		res->numbers->sinal='-';
		cout<<endl;
		t.add( InfCompare(InfSub(x,y), res));
		InfPrint(x);
		InfPrint(y);
		InfPrint(InfSub(x,y));
	}
	{
		char a[]="-25";
		char b[]="4";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("29");
		res->numbers->sinal='-';
		cout<<endl;
		t.add( InfCompare(InfSub(x,y), res));
		InfPrint(x);
		InfPrint(y);
		InfPrint(InfSub(x,y));
	}
	t.close();
}

void teste_InfMult(){
	t.open("InfMult:",10);
	{
		char a[]="1";
		char b[]="2";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("2");
		res->numbers->sinal='+';
		t.add( InfCompare(InfMult(x,y), res));
	}
	{
		char a[]="1";
		char b[]="-2";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("2");
		res->numbers->sinal='-';
		t.add( InfCompare(InfMult(x,y), res));
	}
	{
		char a[]="1223";
		char b[]="22";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("26906");
		res->numbers->sinal='+';
		t.add( InfCompare(InfMult(x,y), res));
	}
	{
		char a[]="-1223";
		char b[]="22";
		InfNumber * x=InfConvert(a);
		InfNumber * y=InfConvert(b);
		InfNumber * res=InfCreateTwo("26906");
		res->numbers->sinal='-';
		t.add( InfCompare(InfMult(x,y), res));
	}
	t.close();
}

int main(){
	testa_InfSum();
	teste_InfSub();
	teste_InfMult();
	t.total();
    return 0;
}


