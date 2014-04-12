// 03 31 2013 P114 eg6-5(transformed)

// author: Andy Zhu

# define LOW 1
# include <iostream>

using namespace std;

int main()
{
	char ch;
	cout <<"input ch:";
	cin >>ch;
	# if LOW
	if (ch >= 'A' && ch<= 'Z') 
		ch = ch + 32;
	# else
	if (ch >= 'a' && ch <= 'z')
		ch = ch - 32;
	#endif
	cout <<ch <<endl;
	return 0;
}
