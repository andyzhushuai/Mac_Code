// 03 31 2013 P105 eg6-4(02)

//author: Andy Zhu

# include <iostream>

# define F(x) ((x)*(x)*(x) + (x)*(x))

using namespace std;

int main()
{
	double f,x,y;
	cout <<"input x,y: ";
	cin >>x >>y;
	f = F(x)*F(y+1);
	cout <<"f = " <<f <<endl;
	return 0;
}
