#include<iostream>
#include<cassert>
#include<vector>
using namespace std;
int main()
{
	vector<string> v(5, "hello");
	vector<string> v2(v.begin(), v.end());

	assert(v == v2);
	cout<<"> Before operation"<<endl;
	for(vector<string>::const_iterator it = v.begin(); it < v.end(); it++)
		cout<<*it<<endl;
	v.insert(v.begin() + 3, 4, "hello, world");
	cout<<"> After insert"<<endl;
	for(vector<string>::size_type i = 0; i < v.size(); i++)
		cout<<v[i]<<endl;

//	vector<string>::iterator it = v.erase(v.begin() + 3, v.begin() + 6);
//	assert(*it == "hello, world");
	vector<string>::iterator it = v.erase(v.begin() + 3, v.begin() + 7);
	assert(*it == "hello");
	cout<<"> After erase"<<endl;
	for(vector<string>::size_type i = 0; i < v.size(); i++)
		cout<<v[i]<<endl;

	assert(v.begin() + v.size() == v.end());
	assert(v.end() - v.size() == v.begin());
	assert(v.begin() - v.end() == -vector<string>::difference_type(v.size()));

	return 0;
}
