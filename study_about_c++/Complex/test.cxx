#include<iostream>
#include<complex.h>
#include<stdio.h>

using namespace std;

int main()
{
	double complex x = 5-5*I;
	double complex y = 5+5*I;
	double complex z = x*y;
//	double  a = double (z);
	double xRe = creal(x);
	double xIm = cimag(x);
	double yRe = creal(y);
	double yIm = cimag(y);
	double zRe = creal(z);
	double zIm = cimag(z);
//	cout<<"Complex x = "<<xRe<<" + ("<<xIm<<")*i"<<endl;
//	cout<<"Complex y = "<<yRe<<" + ("<<yIm<<")*i"<<endl;
//	cout<<"Complex z = "<<zRe<<" + ("<<zIm<<")*i"<<endl;
	printf("Complex x = %f + (%f)*i\n",xRe, xIm);
	printf("Complex y = %f + (%f)*i\n",yRe, yIm);
	printf("Complex z = %f + (%f)*i\n",zRe, zIm);
	return 0;
}
