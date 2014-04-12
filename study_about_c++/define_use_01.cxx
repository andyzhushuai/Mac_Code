//03 31 2013 P105 eg 6-2

//author: Andy Zhu

# include <iostream>

# define V(a,b,c) a*b*c

using namespace std;

int main()
{
	double vsum;
	vsum = V(3.0,4.0,5.0) + V(11.0,23.0,45.0);
	cout <<"vsum = " <<vsum <<endl;
	return 0;
}
