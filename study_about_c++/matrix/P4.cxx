#include <iostream>

using namespace std;

int main()
{
	double P4[4][4] = {0};
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
		{
			cout<<"P4["<< i <<"]["<< j<<"]: "<<P4[i][j]<<endl;
		}
	return 0;
}
